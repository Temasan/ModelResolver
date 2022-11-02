//
// Created by artem on 01.11.2022.
//

#include <gtest/gtest.h>
#include "../header/EquationNodes/TypedEquationNode.h"
#include "../header/EquationMaking/EquationCreator.h"

TEST(EquationCreator, one_operation_sum){
    auto rs = EquationCreator<TypedEquationNode>().make("1 + 2");
    ASSERT_EQ(rs.first->get<int>(), 3);
}

TEST(EquationCreator, one_operation_minus){
    auto rs = EquationCreator<TypedEquationNode>().make("1 - 2");
    ASSERT_EQ(rs.first->get<int>(), -1);
}