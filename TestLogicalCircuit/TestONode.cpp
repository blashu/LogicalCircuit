#include "TestONode.h"

#include "ONode.h"
#include "INode.h"
#include "gtest/gtest.h"

TEST(ONode_ConnectNode,NodeIsNULL)
{
    ONode oNode;

    oNode.connect_node( NULL );
    EXPECT_EQ( NULL, oNode.connected_node() );
}

TEST(ONode_ConnectNode,NormalConnection)
{
    ONode oNode;
    INode iNode;

    oNode.connect_node( &iNode );
    EXPECT_EQ( &iNode, oNode.connected_node() );
}
