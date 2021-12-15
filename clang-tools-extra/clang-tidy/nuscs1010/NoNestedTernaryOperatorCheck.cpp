//===--- NoNestedTernaryOperatorCheck.cpp - clang-tidy --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoNestedTernaryOperatorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoNestedTernaryOperatorCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource,
               conditionalOperator(
                   hasDescendant(conditionalOperator().bind("inner")))
                   .bind("outer")),
      this);
}

void NoNestedTernaryOperatorCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl =
      Result.Nodes.getNodeAs<ConditionalOperator>("inner");
  diag(MatchedDecl->getExprLoc(), "nested ternary operator used",
       DiagnosticIDs::Error);
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
