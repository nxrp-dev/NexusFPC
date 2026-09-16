# NexusFPC Mission Statement

## Purpose

NexusFPC is a focused downstream distribution of Free Pascal.

Its purpose is not to replace Free Pascal, compete with it, or create a separate Pascal ecosystem. Its purpose is to narrow the enormous surface area of the upstream compiler and libraries to the platforms and use cases Nexus actually intends to support, so that those targets can be tested comprehensively, maintained efficiently, and released quickly and reliably.

Free Pascal has accumulated decades of platform support, compatibility layers, libraries, packages, and historical targets. That breadth is valuable to users who need it, but it also creates substantial maintenance and release complexity.

NexusFPC deliberately makes a different tradeoff.

It supports a smaller, explicitly defined set of modern targets. Code, packages, compatibility layers, and platform implementations that have no meaningful role in that supported set may be removed. Reducing that surface area allows the remaining compiler, RTL, libraries, build machinery, and tests to receive substantially more focused attention.

The goal is not maximum compatibility.

The goal is a dependable, maintainable Pascal toolchain for modern application development.

The following are currently supported.  

| Platform | CPUs to retain |
|---|---|
| Windows desktop | x86-64, ARM64 |
| Windows Server | x86-64 |
| Linux desktop/server | x86-64, ARM64 |
| macOS | ARM64 and Intel x86-64 |
| Android | ARM64; x86-64 for emulator testing |
| iPhone/iPad | ARM64 |
| iOS Simulator | ARM64, x86-64 |

## Relationship to Free Pascal

NexusFPC remains downstream of Free Pascal by design.

General compiler improvements, optimizer fixes, RTL fixes, language corrections, and broadly useful features should be contributed to upstream Free Pascal whenever practical. NexusFPC should inherit those improvements through normal synchronization rather than becoming a competing development center.

In general:

```text
General FPC bug, fix, or feature
    → contribute upstream to Free Pascal

NexusFPC pruning, release, integration, or reduced-tree issue
    → contribute to NexusFPC
```

NexusFPC exists to curate, narrow, test, and release a focused subset of FPC—not to fragment FPC development.

## Compatibility Philosophy

Nexus will not depend on NexusFPC-specific language features, ABI changes, proprietary behavior, or other changes that force developers to use NexusFPC.

A developer who needs a platform, target, package, or compatibility feature intentionally omitted from NexusFPC should remain free to use upstream Free Pascal or another compatible FPC toolchain.

NexusFPC may change defaults, remove unsupported targets, retire obsolete compatibility paths, simplify maintenance, and adopt useful upstream development features as part of its supported baseline. Those decisions should improve the focused Nexus toolchain without making Nexus source needlessly dependent on a private compiler dialect.

## Scope

NexusFPC will prioritize the platforms, CPUs, runtime facilities, and packages that materially support modern Nexus development.

Code that exists only to support obsolete, irrelevant, historical, or unsupported environments may be removed when doing so reduces maintenance burden and simplifies the remaining system.

The goal is not maximum target count.

The goal is a compiler distribution small enough to understand, test comprehensively, maintain confidently, and release quickly.

## Maintenance Model

NexusFPC will periodically synchronize with upstream Free Pascal and selectively retain changes relevant to the Nexus-supported surface.

As NexusFPC becomes more focused, upstream remains an important source of compiler engineering, bug fixes, optimizer improvements, platform work, and RTL development.

NexusFPC should minimize unnecessary divergence so that useful upstream work can continue to flow downstream naturally.

## Community

NexusFPC should strengthen, not weaken, the broader Free Pascal ecosystem.

Developers who discover Free Pascal through Nexus may become FPC users or contributors. Bugs found through Nexus may produce fixes useful to upstream FPC. Contributors working on general-purpose compiler improvements should be encouraged to submit them upstream first.

A healthy relationship looks like:

```text
Free Pascal
    broad upstream compiler
        ↓
NexusFPC
    focused, curated, tested downstream
        ↓
Nexus developers and users
        ↓
general fixes and improvements
        ↖ upstream Free Pascal
```

## Mission

> **NexusFPC exists to provide a focused, modern, rapidly maintainable Free Pascal toolchain for Nexus while remaining compatible with and supportive of the broader Free Pascal ecosystem.**
>
> **We narrow the problem so we can test it thoroughly, maintain it quickly, and release it confidently. We do not narrow the community.**
