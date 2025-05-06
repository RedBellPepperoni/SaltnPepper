/************************************************************************|
|						    Test_Vector2.cpp						     |
|************************************************************************|
|                                                                        |
|========================================================================|
|				Copyright (c) 2024 - present Abhishek Dalvi.             |
|																		 |
|                                                                        |
|  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       |
|  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    |
|  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.|
|  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  |
|  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  |
|  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     |
|  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                |
**************************************************************************/

#include <gtest/gtest.h>
#include "Math/Vectors/Vector2.hpp" 
#include <string>
#include <sstream> // For string comparison if needed
#include <cmath>

using Vector2 = SproutEngine::Maths::Vector2;
const float FLOAT_TOLERANCE = 1e-6f;

/// =========================== Test Fixture for Vector2 ============================================
class Vector2Test : public ::testing::Test {
protected:
    Vector2 v1{ 1.0f, 2.0f };
    Vector2 v2{ 3.0f, 4.0f };
    Vector2 zero = Vector2::Zero;
};

// Test Cases
TEST_F(Vector2Test, DefaultConstructor) {
    Vector2 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST_F(Vector2Test, SingleValueConstructor) {
    Vector2 v(5.5f);
    EXPECT_FLOAT_EQ(v.x, 5.5f);
    EXPECT_FLOAT_EQ(v.y, 5.5f);
}

TEST_F(Vector2Test, MultiValueConstructor) {
    Vector2 v(1.2f, 3.4f);
    EXPECT_FLOAT_EQ(v.x, 1.2f);
    EXPECT_FLOAT_EQ(v.y, 3.4f);
}

TEST_F(Vector2Test, CopyConstructor) {
    Vector2 original(1.1f, 2.2f);
    Vector2 copy(original);
    EXPECT_FLOAT_EQ(copy.x, 1.1f);
    EXPECT_FLOAT_EQ(copy.y, 2.2f);

    // Making sure it's a deep copy (modifying copy shouldn't affect original)
    copy.x = 5.5f;
    EXPECT_FLOAT_EQ(original.x, 1.1f);
}

TEST_F(Vector2Test, CopyAssignment) {
    Vector2 original(1.1f, 2.2f);
    Vector2 assigned;
    assigned = original;
    EXPECT_FLOAT_EQ(assigned.x, 1.1f);
    EXPECT_FLOAT_EQ(assigned.y, 2.2f);

    //Making sure it's a deep copy (modifying assigned shouldn't affect original)
    assigned.x = 5.5f;
    EXPECT_FLOAT_EQ(original.x, 1.1f);
}


TEST_F(Vector2Test, UnionXY_UV_Access) {
    Vector2 v;
    v.x = 10.0f;
    EXPECT_FLOAT_EQ(v.u, 10.0f); // Check u reflects x change
    v.v = 20.0f;
    EXPECT_FLOAT_EQ(v.y, 20.0f); // Check y reflects v change
    v.y = 30.0f;
    EXPECT_FLOAT_EQ(v.v, 30.0f); // Check v reflects y change
    v.u = 40.0f;
    EXPECT_FLOAT_EQ(v.x, 40.0f); // Check x reflects u change

    // Also check DirectX SIMD implementation access
    v.xmvector.x = 50.0f;
    EXPECT_FLOAT_EQ(v.x, 50.0f);
    EXPECT_FLOAT_EQ(v.u, 50.0f);
    v.xmvector.y = 60.0f;
    EXPECT_FLOAT_EQ(v.y, 60.0f);
    EXPECT_FLOAT_EQ(v.v, 60.0f);
}

//TEST_F(Vector2Test, ToStringZero) {
//    // Note: The exact format "(0, 0)" depends on the implementation.
//    // Adjust if the actual format includes decimals like "(0.0, 0.0)".
//    std::ostringstream oss_expected;
//    oss_expected << "(" << 0.0f << ", " << 0.0f << ")";
//    EXPECT_EQ(Vector2::Zero.ToString(), oss_expected.str());
//}

//TEST_F(Vector2Test, ToStringCustom) {
//    Vector2 v(1.2f, -3.45f);
//    std::ostringstream oss_expected;
//    oss_expected << "(" << 1.2f << ", " << -3.45f << ")";
//    EXPECT_EQ(v.ToString(), oss_expected.str());
//}

TEST_F(Vector2Test, Addition) {
    Vector2 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector2Test, Subtraction) {
    Vector2 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, -2.0f);
    EXPECT_FLOAT_EQ(result.y, -2.0f);
}

TEST_F(Vector2Test, MultiplicationScalar) {
    Vector2 result = v1 * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector2Test, DivisionScalar) {
    Vector2 result = v2 / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 1.5f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector2Test, DivisionScalarByZero) {
    
   Vector2 result = v1 / 0.0f;

   //Direct X makes division by Zero actual to INF

   bool is_inf = std::isinf(result.x) && std::isinf(result.y);
   EXPECT_TRUE(is_inf); // Accept either INF or zero for zero vector
}

TEST_F(Vector2Test, Length) {
    Vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
    EXPECT_FLOAT_EQ(Vector2::Zero.Length(), 0.0f);
}

TEST_F(Vector2Test, LengthSquared) {
    Vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
    EXPECT_FLOAT_EQ(Vector2::Zero.LengthSquared(), 0.0f);
}

TEST_F(Vector2Test, Normalize) {
    Vector2 v(3.0f, 4.0f);
    v.Normalize();
    EXPECT_NEAR(v.Length(), 1.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v.x, 3.0f / 5.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v.y, 4.0f / 5.0f, FLOAT_TOLERANCE);

    Vector2 v_unit(1.0f, 1.0f);
    v_unit.Normalize();
    EXPECT_NEAR(v_unit.Length(), 1.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v_unit.x, 1.0f / sqrt(2.0f), FLOAT_TOLERANCE);
    EXPECT_NEAR(v_unit.y, 1.0f / sqrt(2.0f), FLOAT_TOLERANCE);
}

TEST_F(Vector2Test, NormalizeZeroVector) {
    Vector2 v = Vector2::Zero;
    v.Normalize(); //DirectX typically results in NaN.


    bool is_nan = std::isnan(v.x) && std::isnan(v.y);
    bool is_zero = (v.x == 0.0f && v.y == 0.0f);
    EXPECT_TRUE(is_nan || is_zero); // Accept either NaN or zero for zero vector normalization
}


TEST_F(Vector2Test, DotProduct) {
    Vector2 vX(1.0f, 0.0f);
    Vector2 vY(0.0f, 1.0f);
    Vector2 vDiag(1.0f, 1.0f);

    EXPECT_FLOAT_EQ(v1.Dot(v2), (1.0f * 3.0f) + (2.0f * 4.0f)); // 3 + 8 = 11
    EXPECT_FLOAT_EQ(vX.Dot(vY), 0.0f); // Orthogonal
    EXPECT_FLOAT_EQ(vDiag.Dot(vDiag), 2.0f); // Parallel with self
}

TEST_F(Vector2Test, Equality) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(1.0f, 2.0f);
    Vector2 c(1.0f, 3.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(Vector2Test, Inequality) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(1.0f, 2.0f);
    Vector2 c(1.0f, 3.0f);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}

TEST_F(Vector2Test, UnaryMinus) {
    Vector2 v(1.5f, -2.5f);
    Vector2 neg_v = -v;
    EXPECT_FLOAT_EQ(neg_v.x, -1.5f);
    EXPECT_FLOAT_EQ(neg_v.y, 2.5f);
}

TEST_F(Vector2Test, StaticMembers) {
    EXPECT_FLOAT_EQ(Vector2::Zero.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector2::Zero.y, 0.0f);
    EXPECT_FLOAT_EQ(Vector2::One.x, 1.0f);
    EXPECT_FLOAT_EQ(Vector2::One.y, 1.0f);
    EXPECT_FLOAT_EQ(Vector2::UnitX.x, 1.0f);
    EXPECT_FLOAT_EQ(Vector2::UnitX.y, 0.0f);
    EXPECT_FLOAT_EQ(Vector2::UnitY.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector2::UnitY.y, 1.0f);
}
