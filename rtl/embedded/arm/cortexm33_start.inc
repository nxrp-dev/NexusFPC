var
 _stack_top: record end; external name '_stack_top';
 _data: record end; external name '_data';
 _edata: record end; external name '_edata';
 _text_start: record end; external name '_text_start';
 _etext: record end; external name '_etext';
 _bss_start: record end; external name '_bss_start';
 _bss_end: record end; external name '_bss_end';

{$DEFINE REMAP_VECTTAB}

{$I cortexm33.inc}

procedure Pascalmain; external name 'PASCALMAIN';

procedure HaltProc; assembler; nostackframe; public name'_haltproc'; noreturn;
asm
.Lloop:
   b .Lloop
end;

procedure Startup; assembler; nostackframe; noreturn; [public, alias: '_START'];
asm
  ldr r0, .Ltext_start
{$ifdef REMAP_VECTTAB}
  ldr r1, .Lvtor
  str r0, [r1]
{$endif REMAP_VECTTAB}
  ldmia r0!, {r1, r2} // r1=stack pointer, r2=entry point
  msr msp, r1
  mov r2, #0x800
  sub r1,r1,r2
  msr psp, r1         // set psp = msp - 2048 bytes
// copy ram consts
  ldr r1,.L_etext
  ldr r2,.L_data
  ldr r3,.L_edata
.Lcopyloop:
  cmp r2,r3
  ittt ls
  ldrls r0,[r1],#4
  strls r0,[r2],#4
  bls .Lcopyloop

// clear onboard ram
  ldr r1,.L_bss_start
  ldr r2,.L_bss_end
  mov r0,#0
.Lzeroloop:
  cmp r1,r2
  itt ls
  strls r0,[r1],#4
  bls .Lzeroloop
// enable coprocessors
  ldr r0, .L_CPACR
  ldr r1, [r0]
//  orr r1, r1, #0xF00000 //; Enables CP10 and CP11 (FPU)
  orr r1, r1, #0xFFFFFF //; Enables all coprocessors
  str r1, [r0]          //; writes to CPACR
  mov r0, #6
  msr CONTROL, r0       // enables PSP as SP and FPU context
  isb
  bl PASCALMAIN
  b HaltProc

.L_CPACR:
  .long 0xE000ED88

.L_bss_start:
  .long _bss_start
.L_bss_end:
  .long _bss_end
.L_etext:
  .long _etext
.L_data:
  .long _data
.L_edata:
  .long _edata
{$ifdef REMAP_VECTTAB}
.Lvtor:
  .long 0xE000ED08
.Ltext_start:
  .long _text_start
{$endif REMAP_VECTTAB}
end;
