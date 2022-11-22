//
// Created by artem on 01.11.2022.
//

#include <gtest/gtest.h>
#include "../header/EquationNodes/TypedEquationNode.h"
#include "../header/EquationMaking/EquationCreator.h"

TEST(EquationCreator, const_and_variable_splitting){
    ASSERT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2").second.size(), 0);
    ASSERT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 + 3").second.size(), 0);
    ASSERT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 + value1").second.size(), 1);
    ASSERT_EQ(EquationCreator<TypedEquationNode>().make("value2 + 2 + value1").second.size(), 2);
    // TODO append join operation
    ASSERT_EQ(EquationCreator<TypedEquationNode>().make("value1 + 2 + value1").second.size(), 2);
}

TEST(EquationCreator, const_one_operations){
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2").first->get<int>(), 3);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 - 2").first->get<int>(), -1);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 * 2").first->get<int>(), 2);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 / 2").first->get<int>(), 0);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 / 2").first->get<double>(), 0.5);
}

TEST(EquationCreator, const_multiple_operation){
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 + 3").first->get<int>(), 6);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 - 3").first->get<int>(), 0);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("5 - 1 + 2 + 3").first->get<int>(), 9);
}

TEST(EquationCreator, const_multiple_operation_without_space){
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 + 3").first->get<int>(), 6);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 - 3").first->get<int>(), 0);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("5 - 1 + 2 + 3").first->get<int>(), 9);
}

TEST(EquationCreator, const_ordered_operations){
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 + 2 * 3").first->get<int>(), 7);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 * 2 + 3 * 4").first->get<int>(), 14);
    EXPECT_EQ(EquationCreator<TypedEquationNode>().make("1 * 2 / 4.0 + 3 * 4").first->get<double>(), 12.5);
}
