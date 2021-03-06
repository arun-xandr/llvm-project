//===-- TargetOptionsImpl.cpp - Options that apply to all targets ----------==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the methods in the TargetOptions.
//
//===----------------------------------------------------------------------===//

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Target/TargetOptions.h"
using namespace llvm;

/// DisableFramePointerElim - This returns true if frame pointer elimination
/// optimization should be disabled for the given machine function.
bool TargetOptions::DisableFramePointerElim(const MachineFunction &MF) const {
  // Check to see if the target want to forcably keep frame pointer.
  if (MF.getSubtarget().getFrameLowering()->keepFramePointer(MF))
    return true;

  const Function &F = MF.getFunction();

  if (!F.hasFnAttribute("frame-pointer"))
    return false;
  StringRef FP = F.getFnAttribute("frame-pointer").getValueAsString();
  if (FP == "all")
    return true;
  if (FP == "non-leaf")
    return MF.getFrameInfo().hasCalls();
  if (FP == "none")
    return false;
  llvm_unreachable("unknown frame pointer flag");
}

/// HonorSignDependentRoundingFPMath - Return true if the codegen must assume
/// that the rounding mode of the FPU can change from its default.
bool TargetOptions::HonorSignDependentRoundingFPMath() const {
  return !UnsafeFPMath && HonorSignDependentRoundingFPMathOption;
}

/// NOTE: There are targets that still do not support the call site info
/// production (the info about the arguments passed to the call, necessary
/// for the debug entry values), so we keep using the experimental option
/// (-debug-entry-values) to test them as well.
bool TargetOptions::ShouldEmitDebugEntryValues() const {
  return SupportsDebugEntryValues || EnableDebugEntryValues;
}
