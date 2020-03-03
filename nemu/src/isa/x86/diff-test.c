#include "nemu.h"
#include "monitor/diff-test.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  if(ref_r->eax != cpu.eax ||
     ref_r->ecx != cpu.ecx ||
     ref_r->edx != cpu.edx ||
     ref_r->ebx != cpu.ebx ||
     ref_r->esp != cpu.esp ||
     ref_r->ebp != cpu.ebp ||
     ref_r->esi != cpu.esi ||
     ref_r->edi != cpu.edi ||
     ref_r->pc  != cpu.pc ) {
      printf("qemu:eax: 0x%08x, nemu eax: 0x%08x, at pc:0x%08x\n", ref_r->eax, cpu.eax, pc);
      printf("qemu:ecx: 0x%08x, nemu ecx: 0x%08x, at pc:0x%08x\n", ref_r->ecx, cpu.ecx, pc);
      printf("qemu:edx: 0x%08x, nemu edx: 0x%08x, at pc:0x%08x\n", ref_r->edx, cpu.edx, pc);
      printf("qemu:ebx: 0x%08x, nemu ebx: 0x%08x, at pc:0x%08x\n", ref_r->ebx, cpu.ebx, pc);
      printf("qemu:esp: 0x%08x, nemu esp: 0x%08x, at pc:0x%08x\n", ref_r->esp, cpu.esp, pc);
      printf("qemu:ebp: 0x%08x, nemu ebp: 0x%08x, at pc:0x%08x\n", ref_r->ebp, cpu.ebp, pc);
      printf("qemu:esi: 0x%08x, nemu esi: 0x%08x, at pc:0x%08x\n", ref_r->esi, cpu.esi, pc);
      printf("qemu:edi: 0x%08x, nemu edi: 0x%08x, at pc:0x%08x\n", ref_r->edi, cpu.edi, pc);
      printf("qemu:eip: 0x%08x, nemu pc: 0x%08x, at pc:0x%08x\n",  ref_r->pc,  cpu.pc,  pc);
    return false;
  }
  return true;
}

void isa_difftest_attach(void) {
}
