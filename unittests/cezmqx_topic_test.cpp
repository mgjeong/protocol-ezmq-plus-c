/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#include <gtest.h>
#include <gmock.h>

#include "cezmqxendpoint.h"
#include "cezmqxtopic.h"

class CEZMQXTopicTest : public testing::Test
{
    protected:
        ezmqxTopicHandle_t topicHandle;
        ezmqxEPHandle_t endPointHandle;
        virtual void SetUp()
        {
            ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic(&topicHandle));
        }

        virtual void TearDown()
        {
            ASSERT_EQ(CEZMQX_OK, ezmqxDestroyTopic(topicHandle));
        }
};

TEST_F(CEZMQXTopicTest, createTopic)
{
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateEndPoint2("address", 5562, &endPointHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "schema", 0, endPointHandle, &topicHandle));
    ASSERT_EQ(CEZMQX_INVALID_PARAM, ezmqxCreateTopic1("topic", "schema", 0, endPointHandle, NULL));
    ASSERT_EQ(CEZMQX_INVALID_PARAM, ezmqxCreateTopic1("topic", "schema", 0, NULL, &topicHandle));
}

TEST_F(CEZMQXTopicTest, destroyTopic)
{
    ASSERT_EQ(CEZMQX_INVALID_PARAM, ezmqxDestroyTopic(NULL));
}

TEST_F(CEZMQXTopicTest, getEndpoint)
{
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateEndPoint2("address", 5562, &endPointHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "schema", 0, endPointHandle, &topicHandle));
    ezmqxEPHandle_t epHandle;
    CEZMQXErrorCode getEPResult = ezmqxGetEndpoint(topicHandle, &epHandle);
    char *address;
    CEZMQXErrorCode getAddrResult = ezmqxGetAddr(epHandle, &address);
    //Free the end point
    ezmqxDestroyEndPoint(epHandle);
    ASSERT_EQ(CEZMQX_OK, getEPResult);
    ASSERT_EQ(CEZMQX_OK, getAddrResult);
    if(0 != strcmp("address", address))
    {
        EXPECT_EQ(CEZMQX_OK, CEZMQX_INVALID_PARAM);
    }
}

TEST_F(CEZMQXTopicTest, getTopic)
{
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateEndPoint2("address", 5562, &endPointHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "schema", 0, endPointHandle, &topicHandle));
    char *topic;
    ASSERT_EQ(CEZMQX_OK, ezmqxGetName(topicHandle, &topic));
    if(0 != strcmp("topic", topic))
    {
        EXPECT_EQ(CEZMQX_OK, CEZMQX_INVALID_PARAM);
    }
}

TEST_F(CEZMQXTopicTest, getDataModel)
{
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateEndPoint2("address", 5562, &endPointHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "dataModel", 0, endPointHandle, &topicHandle));
    char *dataModel;
    ASSERT_EQ(CEZMQX_OK, ezmqxGetDatamodel(topicHandle, &dataModel));
    if(0 != strcmp("dataModel", dataModel))
    {
        EXPECT_EQ(CEZMQX_OK, CEZMQX_INVALID_PARAM);
    }
}

TEST_F(CEZMQXTopicTest, isSecured)
{
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateEndPoint2("address", 5562, &endPointHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "schema", 0, endPointHandle, &topicHandle));
    ASSERT_EQ(0, ezmqxIsTopicSecured(topicHandle));
    ASSERT_EQ(CEZMQX_OK, ezmqxCreateTopic1("topic", "schema", 1, endPointHandle, &topicHandle));
    ASSERT_EQ(1, ezmqxIsTopicSecured(topicHandle));
}

