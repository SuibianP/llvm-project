//===--- NUSCS1010TidyModule.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "ForbiddenTypesCheck.h"
#include "NoBreakCheck.h"
#include "NoContinueCheck.h"
#include "NoGotoCheck.h"

#include "../readability/BracesAroundStatementsCheck.h"

namespace clang {
namespace tidy {
namespace nuscs1010 {

class NUSCS1010Module : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<ForbiddenTypesCheck>(
        "nuscs1010-forbidden-types");
    CheckFactories.registerCheck<NoBreakCheck>("nuscs1010-no-break");
    CheckFactories.registerCheck<NoContinueCheck>("nuscs1010-no-continue");
    CheckFactories.registerCheck<NoGotoCheck>("nuscs1010-no-goto");
    CheckFactories.registerCheck<readability::BracesAroundStatementsCheck>(
        "nuscs1010-braces-around-statements");
  }
};

// Register the NUSCS1010Module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<NUSCS1010Module>
    X("nus-cs1010-module", "Adds NUS CS1010 checks.");

} // namespace nuscs1010

// This anchor is used to force the linker to link in the generated object file
// and thus register the NUSCS1010Module.
volatile int NUSCS1010ModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
