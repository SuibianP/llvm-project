//===--- NoGotoCheck.cpp - clang-tidy -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

/*
 * This is not a duplicate of cppcoreguidelines-avoid-goto
 * since we disallow forward gotos as well
 */

#include "NoGotoCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoGotoCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource, gotoStmt().bind("goto")), this);
}

void NoGotoCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Goto = Result.Nodes.getNodeAs<GotoStmt>("goto");
  diag(Goto->getGotoLoc(), "using goto is disallowed", DiagnosticIDs::Error)
      << Goto->getSourceRange();
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
