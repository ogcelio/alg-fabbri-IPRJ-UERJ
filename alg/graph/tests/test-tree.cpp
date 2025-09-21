/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#include <gtest/gtest.h>
#include "tree.h"

TEST(TreeTest, BasicInsertion) {
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Capture stdout to check inorder traversal
    testing::internal::CaptureStdout();
    inorder(root);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "20 30 40 50 60 70 80 ");
}
