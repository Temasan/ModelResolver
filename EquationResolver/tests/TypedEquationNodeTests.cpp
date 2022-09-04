//
// Created by artem on 28.08.2022.
//

#include <gtest/gtest.h>
#include "../header/EquationNodes/TypedEquationNode.h"
TEST(TypedEquationNode, type_int){
    auto nodeLeft = TypedEquationNode::make_node(1);
    auto nodeRight = TypedEquationNode::make_node(2);
    auto nodeMain = TypedEquationNode::make_node(0, EquationRules::Rule::sum, nodeLeft, nodeRight);
    ASSERT_EQ(nodeMain->get<int>(), 3);
    ASSERT_EQ(nodeMain->get<double>(), 3.);
}

TEST(TypedEquationNode, type_double){
    auto nodeLeft = TypedEquationNode::make_node(1.5);
    auto nodeRight = TypedEquationNode::make_node(2.);
    auto nodeMain = TypedEquationNode::make_node(0., EquationRules::Rule::sum, nodeLeft, nodeRight);
    ASSERT_EQ(nodeMain->get<double>(), 3.5);
    ASSERT_EQ(nodeMain->get<int>(), 3);
}

TEST(TypedEquationNode, node_recalculating){
    auto nodeLeft = TypedEquationNode::make_node(1.5);
    auto nodeRight = TypedEquationNode::make_node(2.);
    auto nodeMain = TypedEquationNode::make_node(0., EquationRules::Rule::sum, nodeLeft, nodeRight);
    ASSERT_EQ(nodeMain->get<double>(), 3.5);
    ASSERT_EQ(nodeMain->get<int>(), 3);

    nodeLeft->setValue(3.5);
    ASSERT_EQ(nodeMain->get<double>(), 5.5);
    ASSERT_EQ(nodeMain->get<int>(), 5);

    nodeRight->setValue(6.5);
    ASSERT_EQ(nodeMain->get<double>(), 10.);
    ASSERT_EQ(nodeMain->get<int>(), 10);
}

TEST(TypedEquationNode, type_deduction_recalculating){
    auto nodeLeft = TypedEquationNode::make_node(1.5);
    auto nodeRight = TypedEquationNode::make_node(2);
    auto nodeMain = TypedEquationNode::make_node(0., EquationRules::Rule::sum, nodeLeft, nodeRight);
    ASSERT_EQ(nodeMain->get<double>(), 3.5);
    ASSERT_EQ(nodeMain->get<int>(), 3);

    nodeLeft->setValue(3);
    ASSERT_EQ(nodeMain->get<double>(), 5.);
    ASSERT_EQ(nodeMain->get<int>(), 5);

    nodeRight->setValue(6.5);
    ASSERT_EQ(nodeMain->get<double>(), 9.);
    ASSERT_EQ(nodeMain->get<int>(), 9);
}

TEST(TypedEquationNode, node_appending){
    auto nodeLeft = TypedEquationNode::make_node(1.5);
    auto nodeRight = TypedEquationNode::make_node(2.);
    auto nodeMain = TypedEquationNode::make_node(0., EquationRules::Rule::sum, nodeLeft, nodeRight);
    ASSERT_EQ(nodeMain->get<double>(), 3.5);
    ASSERT_EQ(nodeMain->get<int>(), 3);

    auto nodeMainRight = TypedEquationNode::make_node(9.);
    auto nodeMainMain = TypedEquationNode::make_node(0., EquationRules::Rule::minus, nodeMain, nodeMainRight);
    ASSERT_EQ(nodeMainMain->get<double>(), -5.5);
    ASSERT_EQ(nodeMainMain->get<int>(), -5);
}