//===--- NoContinueCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoContinueCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoContinueCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource, continueStmt().bind("cont")),
      this);
}

void NoContinueCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Cont = Result.Nodes.getNodeAs<ContinueStmt>("cont");
  diag(Cont->getContinueLoc(), "using continue is discouraged")
      << Cont->getSourceRange();
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
