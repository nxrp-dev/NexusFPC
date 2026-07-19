# FPC machine-readable target/architecture dump — spec request (MR5)

**Date:** 2026-07-19
**Status:** design request for the compiler side — describes *what* to emit and the
*invariants* it must satisfy, not a patch. Format is negotiable; the content and
invariants are the hard requirement.
**Audience:** the FPC compiler project (has the surrounding context in `compiler/options.pas`
and the per-CPU `cpuinfo.pas`).

---

## 1. Why

Tools that build "Target / CPU / MCU" selectors (Lazarus' *Config and Target* page, other
IDEs, build scripts) currently either duplicate the compiler's tables or scrape the
human-formatted `fpc -i` output. Both are bad:

* **Duplication goes stale and lossy.** Lazarus embeds `codetools/controllertypes.inc`, a hand
  maintained projection of `embedded_controllers` that keeps only `(controllertypestr,
  controllerunitstr)`. It has *no RISC-V rows at all* today, and it drops `cputype`, `fputype`
  and the memory map. The MR4 riscv32 controllers (GD32VF103*, CH32V303/305/307*, ESP32-C*,
  `CH32V_IMAC*/IMAFC*`) are invisible to the stock IDE until someone hand-regenerates that
  include.
* **The human `fpc -i` text is display-formatted and lossy.** It line-wraps lists at a column
  width, comma-joins them, and — critically — `-iu` emits controller *names only*. A consumer
  cannot recover, for a given controller, which instruction set (`-Cp`), FPU set (`-Cf`),
  controller unit, or flash/RAM layout it implies. That mapping is exactly what "pick the MCU,
  derive the rest" needs, and it already exists inside the compiler
  (`embedded_controllers : array[tcontrollertype] of tcontrollerdatatype`).

The ask: a **stable, versioned, complete, machine-parseable** dump of what the *installed*
compiler binary supports, so tools stop guessing.

## 2. What to emit (the hard requirement)

All of the following is data the ppc binary already holds. One dump, for the CPU of the binary
invoked (same per-CPU model as `-i` today). Emit for every section, even when a list is empty.

**Compiler identity** — version, build date, compiler target CPU, host OS, host CPU. (Same values
as `-iV`, `-iD`, `-iSP`, `-iSO`.)

**Target OSes** — each supported target OS, with a boolean **`underdevelopment`** flag
corresponding to the `{*}` marker in the human output. Consumers need the flag as data so they
can hide or warn on in-development targets instead of parsing `{*}`.

**CPU instruction sets** — the `-Cp` / `-ic` values, as canonical tokens
(`RV32IMAFC`, `RV32IMAC_ZICSR_ZIFENCEI`, …). These MUST be the exact strings the compiler accepts
for `-Cp` and prints for `-ic`, i.e. `cputypestr[...]` — **not** the internal enum identifiers
(`cpu_rv32imafc`). Cross-referencing (below) depends on this.

**FPU instruction sets** — the `-Cf` / `-if` values as canonical tokens (`NONE`, `LIBGCC`,
`SOFT`, `FS`, `FD`), i.e. `fputypestr[...]`.

**ABIs** — the `-Ca` values (`DEFAULT`, `ILP32`, `ILP32F`, `ILP32D`, `ILP32E`).

**Controllers (the important one)** — for **every** entry of `embedded_controllers`, all fields of
`tcontrollerdatatype`:

| Field        | Source                          | Notes |
|--------------|---------------------------------|-------|
| `name`       | `controllertypestr`             | the `-Wp` value |
| `unit`       | `controllerunitstr`             | may be empty (e.g. the `''` sentinel row); emit it anyway |
| `cpu`        | `cputypestr[cputype]`           | canonical token — MUST match an entry in *CPU instruction sets* |
| `fpu`        | `fputypestr[fputype]`           | canonical token — MUST match an entry in *FPU instruction sets* |
| `flashbase`, `flashsize` | `flashbase`, `flashsize` | resolved integers (see invariants) |
| `srambase`, `sramsize`   | `srambase`, `sramsize`   | |
| `eeprombase`, `eepromsize` | `eeprombase`, `eepromsize` | `0` when unused |
| `bootbase`, `bootsize`     | `bootbase`, `bootsize`     | `0` when unused (set on e.g. `CH32V_EC_16K_2K_2K`) |

**Optional / low priority** (nice for completeness and for versioning tools, but not needed for
target selection): inline-asm modes (`-ii`), optimizations (`-io`), whole-program opts (`-iw`),
RTL/compiler features (`-ir`), recognized modeswitches. Include as flat string arrays if cheap;
skip if it complicates the change.

## 3. Invariants (what makes it usable)

1. **Canonical tokens, cross-referenceable.** `controllers[].cpu` MUST be a member of
   `instructionsets`, and `controllers[].fpu` a member of `fpusets`. This is what lets a consumer
   pick a controller and immediately know the implied `-Cp`/`-Cf` without a second table. Emit
   `cputypestr[]`/`fputypestr[]`, never the Pascal enum identifiers.
2. **Resolved integers.** Several rows use compile-time expressions (`4*1024*1024`, `272*1024`).
   Emit the *resolved* numeric value, not the source expression. Addresses/sizes are `dword`;
   emit them as `$`-prefixed hexadecimal (the Pascal hex convention, matching `cpuinfo.pas`), so a
   Pascal consumer reads them with `StrToInt`/`StrToInt64` directly. Be explicit and consistent
   about base in the format doc (see §5.6).
3. **Stable ordering.** Emit in enum declaration order (or a documented stable order). Don't sort
   by something that reorders across versions.
4. **ASCII, LF, unlocalized.** No language translation of any token or key. `\n` line endings.
5. **Versioned.** A top-level `formatversion` integer, bumped on any breaking schema change, so
   consumers can guard. Additive fields shouldn't bump it.
6. **Additive-only over time.** New CPUs/controllers/fields append; existing field names and
   token spellings don't change meaning.
7. **Complete.** Include the empty/`ct_none` sentinel row or explicitly document its omission —
   don't leave the consumer guessing whether index 0 was dropped.

## 4. Suggested interface

The `-i` letter namespace is nearly full (`-iD/-iV/-iW/-iSO/-iSP/-iTO/-iTP` for single values;
`-ia/-ic/-if/-ii/-io/-ir/-it/-iu/-iw` for lists). Rather than crowd it, a **dedicated long
option** reads cleanest and leaves existing `-i` output untouched:

```
fpc --target-info            # emit the dump to stdout, then exit (like -i)
```

It respects `-P<cpu>` (selects the ppc binary, as today) and `-T<os>`. Whatever the spelling, the
requirements: it's a query-and-exit mode like `-i`, it does not require a source file, and it
does not alter any existing `-i` output. (If the maintainers would rather extend `-i` with a new
letter or a `-i!`-style modifier, that's fine — content and invariants are what matter.)

Controllers are compiled-in independent of `-T`, so emit the full set the binary knows; the
consumer shows them only for `-Tembedded`/`-Tfreertos`. (If it's cheap to tag each controller
with the OS(es) it's valid under, that's a welcome extra, but the table doesn't model it today.)

## 5. Format — human-readable *and* machine-parseable

The data here is **flat**: a few token lists plus one controller table with fixed columns.
Nothing is nested, so there is nothing to gain from JSON/XML expressiveness — and a structured
format walks straight into the format debate that stalled the prior fpc-devel thread ("Public
access of FPC features and settings"), where JSON (Van Canneyt) vs XML (Klämpfl, on the grounds
the node tree is XML) was left unresolved. Sidestep it: emit a **documented, versioned,
one-record-per-line table** that a human can read as a table and a tool can parse by split-and-trim.

In DB terms this is a deliberate **denormalization** — each controller row repeats its `cpu`/`fpu`/
`unit` tokens inline instead of normalizing them into reference tables the consumer would have to
join. The redundancy is trivial (short repeated tokens); the payoff is a consumer that needs no
join logic.

### Recommended format

```
# fpc target-info v1  cpu=riscv32
[TARGETOS]
name     | underdevelopment
linux    | 0
embedded | 0
freertos | 0
[INSTRUCTIONSETS]
RV32IMAC
RV32IMAC_ZICSR_ZIFENCEI
RV32IMAFC
RV32EC
RV32GCB
[FPUSETS]
NONE
FS
FD
[ABIS]
DEFAULT
ILP32
ILP32E
[CONTROLLERS]
name               | unit            | cpu       | fpu  | flashbase  | flashsize  | srambase   | sramsize   | eeprombase | eepromsize | bootbase   | bootsize
CH32V307VC         | CH32V307        | RV32IMAFC | FS   | $00000000 | $00040000 | $20000000 | $00010000 | $00000000 | $00000000 | $00000000 | $00000000
CH32V_EC_16K_2K_2K | CH32VxBootstrap | RV32EC    | NONE | $00000000 | $00004000 | $20000000 | $00000800 | $00000000 | $00000000 | $1FFFF000 | $00000780
```

(Lists and the table are abbreviated above; emit the full sets.)

### Parse contract (what makes it robust, not just pretty)

1. **Version line first.** `# fpc target-info v<N> cpu=<cpu>`. Bump `<N>` only on a breaking
   change. The version + this documented contract are the stability guarantee that separates this
   from "just scrape `-i`" (which promises nothing).
2. **Section markers.** Each section starts with `[NAME]` on its own line, so one stream can carry
   differently-shaped sections unambiguously.
3. **Token lists are one-per-line.** No comma-joining, no column-width wrapping — that wrapping is
   the actual defect in today's `-i`. One token, one line.
4. **Tables carry a named header row.** The first line after `[CONTROLLERS]` names the columns.
   Consumers **key by column name, not position**, so a later column append is additive and does
   not break existing parsers.
5. **One real delimiter: ` | ` (space-pipe-space).** Cells may be space-padded for visual
   alignment, but the parser splits on `|` and trims. No token in this data contains a pipe or a
   space, so this is unambiguous. (Pad for humans; delimit for machines — the `psql`/markdown-table
   trick.)
6. **Numbers.** Addresses and sizes as `$`-prefixed hex — the Pascal hex convention (the
   compiler's own `cpuinfo.pas` tables already write `$20000000`), not C-style `0x`. Bonus: a
   Pascal consumer reads it with `StrToInt`/`StrToInt64` directly, no prefix stripping. Resolve
   compile-time expressions (`4*1024*1024`) to a literal. Document the base once.
7. **ASCII, LF, unlocalized, stable order** (as in §3).

This is dependency-free to emit (it's just formatted text, like `-i` already is) **and**
dependency-free to consume (`TStringList` + split on the Lazarus side — no `fpjson`).

### If a structured format is preferred anyway

If maintainers would rather emit structured data, follow the **existing pas2js JSON message
convention** rather than reopening JSON-vs-XML from scratch — pas2js already ships JSON output, so
"match what pas2js does" is a precedent argument, not a new subsystem. Same content, same
invariants (§2–§3); only the serialization changes.

## 6. Backward compatibility & constraints

* Do **not** change existing `-i`/`-iu`/`-ic` output — tools depend on it.
* **No new compiler-core dependency.** Emit by direct string output.
* Query-and-exit; no source file required; no codegen side effects.
* Deterministic across runs on the same binary.

## 7. Non-goals

* Not a replacement for human `fpc -i`.
* Not an interactive query protocol — a single one-shot dump per invocation.
* Not describing linker scripts or startup code — just the data the compiler already models.

## 8. Acceptance check

For MR4's `ppcrossrv32`:

* `fpc -Priscv32 --target-info` emits the version line, every section marker, and one
  `[CONTROLLERS]` data row per `-iu` name (41 today: FE310* … `CH32V_IMAFC_480K_64K`).
* The `[CONTROLLERS]` header row names the columns; splitting a data row on ` | ` and trimming
  yields exactly those columns.
* For every controller, `cpu` appears in `[INSTRUCTIONSETS]` and `fpu` in `[FPUSETS]`.
* `CH32V307VC` resolves to `unit=CH32V307, cpu=RV32IMAFC, fpu=FS, flashsize=$00040000,
  srambase=$20000000, sramsize=$00010000`.
* ESP32-C rows show *resolved* sizes (e.g. `flashsize=$00400000`), not `4*1024*1024`.
* Existing `fpc -i` output is byte-identical to before.

## Source references (MR4)

* `compiler/riscv32/cpuinfo.pas` — `tcontrollertype` enum, `tcontrollerdatatype` record (fields
  listed in §2), `embedded_controllers` table, `cputypestr[]`, `fputypestr[]`, `cpu_capabilities[]`.
* `compiler/systems/i_embed.pas` — embedded system info (`system_riscv32_embedded_info`).
* `compiler/options.pas` — where `-i` info is currently produced (the natural home for the new
  option).
