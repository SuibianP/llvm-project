//===--- NoBreakCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoBreakCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoBreakCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource, breakStmt().bind("break")),
      this);
}

void NoBreakCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Break = Result.Nodes.getNodeAs<BreakStmt>("break");
  diag(Break->getBreakLoc(), "using break is discouraged")
      << Break->getSourceRange();
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
