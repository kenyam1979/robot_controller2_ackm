// Test items in PhotoEncoder class

#include <gtest/gtest.h>

#include <rclcpp/rclcpp.hpp>

#include "robot_controller2_ackm/photo_encoder.hpp"

namespace controller_tamiya_tt02 {

class PhotoEncoderTest : public ::testing::Test {
 protected:
  void SetUp() override { encoder_ = std::make_shared<PhotoEncoder>(); }

  void TearDown() override {}

  std::shared_ptr<PhotoEncoder> encoder_;
};

class PhotoEncoderTestFriend {
 public:
  void setCountValue(PhotoEncoder &encoder, int n) { encoder.count_ = n; }
  void callEncCB(PhotoEncoder &encoder, void *data) {
    encoder.encCB(0, nullptr, data);
  }
};

// 1. Initialization of the PhotoEncoder class
// 1.1 It shall initialize the photo encoder
TEST_F(PhotoEncoderTest, 1_1_InitializePhotoEncoder) {
  ASSERT_NE(encoder_, nullptr);
  ASSERT_EQ(encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                                 PhotoEncoderSetting::ENC_PIN),
            PhotoEncoderReturnType::OK);
}

// 1.2 It shall return error on photo encoder driver initialization failure
TEST_F(PhotoEncoderTest, 1_2_InitializePhotoEncoderDriverFailure) {
  // Simulate failure by passing invalid parameters
  ASSERT_EQ(encoder_->initialize(1, ENC_PIN),
            PhotoEncoderReturnType::DRIVER_ERROR);
}

// 2. Get RPM from the photo encoder
// 2.1 It shall return the correct RPM based on the count value
TEST_F(PhotoEncoderTest, 2_1_GetRPM) {
  encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                       PhotoEncoderSetting::ENC_PIN);

  auto f = std::make_shared<PhotoEncoderTestFriend>();
  f->setCountValue(*encoder_, 80);

  ASSERT_EQ(encoder_->getRPM(1.0), 120.0);
}

// 2.2 It shall return zero RPM when count is zero
TEST_F(PhotoEncoderTest, 2_2_GetRPMZeroCount) {
  encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                       PhotoEncoderSetting::ENC_PIN);
  ASSERT_EQ(encoder_->reset(), PhotoEncoderReturnType::OK);
  ASSERT_EQ(encoder_->getRPM(1.0), 0.0);
}

// 2.3 It shall return error when diff is zero
TEST_F(PhotoEncoderTest, 2_3_GetRPMZeroDiff) {
  encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                       PhotoEncoderSetting::ENC_PIN);
  auto f = std::make_shared<PhotoEncoderTestFriend>();
  f->setCountValue(*encoder_, 80);
  ASSERT_EQ(encoder_->getRPM(0.0), PhotoEncoderReturnType::ERROR);
}

// 3. Callback function for the photo encoder
// 3.1 It shall increment the count value when called
TEST_F(PhotoEncoderTest, 3_1_CallbackIncrementCount) {
  encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                       PhotoEncoderSetting::ENC_PIN);

  int count = 0;
  auto f = std::make_shared<PhotoEncoderTestFriend>();
  f->callEncCB(*encoder_, &count);
  f->callEncCB(*encoder_, &count);
  f->callEncCB(*encoder_, &count);
  ASSERT_EQ(count, 3);
}

// 4. Reset the photo encoder
// 4.1 It shall reset the count and RPM values
TEST_F(PhotoEncoderTest, 4_1_ResetPhotoEncoder) {
  encoder_->initialize(PhotoEncoderSetting::GPIO_CHIP,
                       PhotoEncoderSetting::ENC_PIN);

  auto f = std::make_shared<PhotoEncoderTestFriend>();
  f->setCountValue(*encoder_, 80);
  encoder_->getRPM(1.0);

  ASSERT_EQ(encoder_->reset(), PhotoEncoderReturnType::OK);
  ASSERT_EQ(encoder_->getRPM(1.0), 0.0);
}

// 4.2 It shall return error on reset failure
TEST_F(PhotoEncoderTest, 4_2_ResetPhotoEncoderFailure) {
  // Simulate failure by not initializing the encoder
  encoder_->initialize(1, ENC_PIN);
  ASSERT_EQ(encoder_->reset(), PhotoEncoderReturnType::DRIVER_ERROR);
}

}  // namespace controller_tamiya_tt02