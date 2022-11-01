//
// Created by artem on 01.11.2022.
//

#include <gtest/gtest.h>
#include "../header/EquationMaking/EquationCreator.h"
#include "../header/EquationNodes/NamedEquationNode.h"

TEST(EquationCreator, one_operation){
    auto rs = EquationCreator<NamedEquationNode::NamedNodeType>().make("1 + 2");
    ASSERT_EQ(rs.first->get<int>(), 3);
}