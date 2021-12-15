//===--- NoIncrDecrOperatorsCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoIncrDecrOperatorsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoIncrDecrOperatorsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(traverse(TK_IgnoreUnlessSpelledInSource,
                              unaryOperator(anyOf(hasOperatorName("++"),
                                                  hasOperatorName("--")))
                                  .bind("optr")),
                     this);
}

void NoIncrDecrOperatorsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<UnaryOperator>("optr");
  diag(MatchedDecl->getOperatorLoc(),
       "unary increment and decrement operators are banned",
       DiagnosticIDs::Error);
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
