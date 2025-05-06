/************************************************************************|
|						    Test_Vector3.cpp						     |
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
#include "Math/Vectors/Vector3.hpp" 
#include <string>
#include <sstream> // For string comparison if needed
#include <cmath>

using Vector3 = SproutEngine::Maths::Vector3;
const float FLOAT_TOLERANCE = 1e-6f;

/// =========================== Test Fixture for Vector3 ============================================
class Vector3Test : public ::testing::Test {
protected:
    Vector3 v1{ 1.0f, 2.0f, 3.0f };
    Vector3 v2{ 3.0f, 4.0f, 5.0f };
    Vector3 zero = Vector3::Zero;
};

// Test Cases
TEST_F(Vector3Test, DefaultConstructor) {
    Vector3 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST_F(Vector3Test, SingleValueConstructor) {
    Vector3 v(5.5f);
    EXPECT_FLOAT_EQ(v.x, 5.5f);
    EXPECT_FLOAT_EQ(v.y, 5.5f);
    EXPECT_FLOAT_EQ(v.z, 5.5f);
}

TEST_F(Vector3Test, MultiValueConstructor) {
    Vector3 v(1.2f, 3.4f, 5.6f);
    EXPECT_FLOAT_EQ(v.x, 1.2f);
    EXPECT_FLOAT_EQ(v.y, 3.4f);
    EXPECT_FLOAT_EQ(v.z, 5.6f);
}

TEST_F(Vector3Test, CopyConstructor) {
    Vector3 original(1.1f, 2.2f, 3.3f);
    Vector3 copy(original);
    EXPECT_FLOAT_EQ(copy.x, 1.1f);
    EXPECT_FLOAT_EQ(copy.y, 2.2f);
    EXPECT_FLOAT_EQ(copy.z, 3.3f);

    // Making sure it's a deep copy (modifying copy shouldn't affect original)
    copy.x = 5.5f;
    EXPECT_FLOAT_EQ(original.x, 1.1f);
}

TEST_F(Vector3Test, CopyAssignment) {
    Vector3 original(1.1f, 2.2f, 3.3f);
    Vector3 assigned;
    assigned = original;
    EXPECT_FLOAT_EQ(assigned.x, 1.1f);
    EXPECT_FLOAT_EQ(assigned.y, 2.2f);
    EXPECT_FLOAT_EQ(assigned.z, 3.3f);

    //Making sure it's a deep copy (modifying assigned shouldn't affect original)
    assigned.x = 5.5f;
    EXPECT_FLOAT_EQ(original.x, 1.1f);
}


TEST_F(Vector3Test, UnionXYZ_UVW_RGB_Access) {
    Vector3 v;
    v.x = 10.0f;
    EXPECT_FLOAT_EQ(v.r, 10.0f); // Check r reflects x change
    v.u = 20.0f;
    EXPECT_FLOAT_EQ(v.x, 20.0f); // Check x reflects u 
    v.r = 30.0f;
    EXPECT_FLOAT_EQ(v.u, 30.0f); // Check u reflects r 


    v.y = 40.0f;
    EXPECT_FLOAT_EQ(v.g, 40.0f); // Check y reflects g change
    v.v = 50.0f;
    EXPECT_FLOAT_EQ(v.y, 50.0f); // Check v reflects y change
    v.g = 60.0f;
    EXPECT_FLOAT_EQ(v.v, 60.0f); // Check v reflects y change
 
    v.z = 50.0f;
    EXPECT_FLOAT_EQ(v.b, 50.0f); // Check z reflects b change
    v.w = 60.0f;
    EXPECT_FLOAT_EQ(v.z, 60.0f); // Check 2 reflects z change
    v.b = 60.0f;
    EXPECT_FLOAT_EQ(v.w, 60.0f); // Check b reflects w change

    // Also check DirectX SIMD implementation access
    v.xmvector.x = 70.0f;
    EXPECT_FLOAT_EQ(v.x, 70.0f);
    EXPECT_FLOAT_EQ(v.u, 70.0f);
    EXPECT_FLOAT_EQ(v.r, 70.0f);

    v.xmvector.y = 80.0f;
    EXPECT_FLOAT_EQ(v.y, 80.0f);
    EXPECT_FLOAT_EQ(v.v, 80.0f);
    EXPECT_FLOAT_EQ(v.g, 80.0f);

    v.xmvector.z = 90.0f;
    EXPECT_FLOAT_EQ(v.z, 90.0f);
    EXPECT_FLOAT_EQ(v.w, 90.0f);
    EXPECT_FLOAT_EQ(v.b, 90.0f);
}

//TEST_F(Vector3Test, ToStringZero) {
//    // Note: The exact format "(0, 0)" depends on the implementation.
//    // Adjust if the actual format includes decimals like "(0.0, 0.0)".
//    std::ostringstream oss_expected;
//    oss_expected << "(" << 0.0f << ", " << 0.0f << ")";
//    EXPECT_EQ(Vector3::Zero.ToString(), oss_expected.str());
//}

//TEST_F(Vector3Test, ToStringCustom) {
//    Vector3 v(1.2f, -3.45f);
//    std::ostringstream oss_expected;
//    oss_expected << "(" << 1.2f << ", " << -3.45f << ")";
//    EXPECT_EQ(v.ToString(), oss_expected.str());
//}

TEST_F(Vector3Test, Addition) {
    Vector3 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector3Test, Subtraction) {
    Vector3 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, -2.0f);
    EXPECT_FLOAT_EQ(result.y, -2.0f);
}

TEST_F(Vector3Test, MultiplicationScalar) {
    Vector3 result = v1 * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector3Test, DivisionScalar) {
    Vector3 result = v2 / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 1.5f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
}

TEST_F(Vector3Test, DivisionScalarByZero) {

    Vector3 result = v1 / 0.0f;

    //Direct X makes division by Zero actual to INF

    bool is_inf = std::isinf(result.x) && std::isinf(result.y);
    EXPECT_TRUE(is_inf); // Accept either INF or zero for zero vector
}

TEST_F(Vector3Test, Length) {
    Vector3 v(2.0f, 3.0f, 6.0f);
    EXPECT_FLOAT_EQ(v.Length(), 7.f);
    EXPECT_FLOAT_EQ(Vector3::Zero.Length(), 0.0f);
}

TEST_F(Vector3Test, LengthSquared) {
    Vector3 v(2.0f, 3.0f, 6.0f);
    EXPECT_FLOAT_EQ(v.LengthSquared(), 49.0f);
    EXPECT_FLOAT_EQ(Vector3::Zero.LengthSquared(), 0.0f);
}

TEST_F(Vector3Test, Normalize) {
    Vector3 v(2.0f, 3.0f, 6.0f);
    v.Normalize();
    EXPECT_NEAR(v.Length(), 1.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v.x, 2.0f / 7.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v.y, 3.0f / 7.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v.z, 6.0f / 7.0f, FLOAT_TOLERANCE);

    Vector3 v_unit = Vector3::One;
    v_unit.Normalize();
    EXPECT_NEAR(v_unit.Length(), 1.0f, FLOAT_TOLERANCE);
    EXPECT_NEAR(v_unit.x, 1.0f / sqrt(3.0f), FLOAT_TOLERANCE);
    EXPECT_NEAR(v_unit.y, 1.0f / sqrt(3.0f), FLOAT_TOLERANCE);
    EXPECT_NEAR(v_unit.z, 1.0f / sqrt(3.0f), FLOAT_TOLERANCE);
}

TEST_F(Vector3Test, NormalizeZeroVector) {
    Vector3 v = Vector3::Zero;
    v.Normalize(); //DirectX typically results in NaN.


    bool is_nan = std::isnan(v.x) && std::isnan(v.y);
    bool is_zero = (v.x == 0.0f && v.y == 0.0f);
    EXPECT_TRUE(is_nan || is_zero); // Accept either NaN or zero for zero vector normalization
}


TEST_F(Vector3Test, DotProduct) {
    Vector3 vX(1.0f, 2.0f, 3.0f);
    Vector3 vY(1.0f, 5.0f, 7.0f);
    Vector3 vDiag(1.0f, 1.0f,1.0f);

    Vector3 vH(1.0f, 0.0f, 0.0f);
    Vector3 vV(0.0f, 1.0f, 0.0f);

    EXPECT_FLOAT_EQ(vX.Dot(vY), 32); // (1*1) + (2*5) + (3*7) = 32
    EXPECT_FLOAT_EQ(vH.Dot(vV), 0.0f); // Orthogonal
    EXPECT_FLOAT_EQ(vDiag.Dot(vDiag), 3.0f); // Parallel with self
}

TEST_F(Vector3Test, Equality) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(1.0f, 2.0f, 3.0f);
    Vector3 c(1.0f, 3.0f, 2.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(Vector3Test, Inequality) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(1.0f, 2.0f, 3.0f);
    Vector3 c(1.0f, 3.0f, 2.0f);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}

TEST_F(Vector3Test, UnaryMinus) 
{
    Vector3 v(1.5f, -2.5f, 2.0f);
    Vector3 neg_v = -v;
    EXPECT_FLOAT_EQ(neg_v.x, -1.5f);
    EXPECT_FLOAT_EQ(neg_v.y, 2.5f);
    EXPECT_FLOAT_EQ(neg_v.z, -2.0f);
}

TEST_F(Vector3Test, StaticMembers) {
    EXPECT_FLOAT_EQ(Vector3::Zero.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector3::Zero.y, 0.0f);
    EXPECT_FLOAT_EQ(Vector3::Zero.z, 0.0f);

    EXPECT_FLOAT_EQ(Vector3::One.r, 1.0f);
    EXPECT_FLOAT_EQ(Vector3::One.g, 1.0f);
    EXPECT_FLOAT_EQ(Vector3::One.b, 1.0f);

    EXPECT_FLOAT_EQ(Vector3::UnitX.x, 1.0f);
    EXPECT_FLOAT_EQ(Vector3::UnitX.y, 0.0f);
    EXPECT_FLOAT_EQ(Vector3::UnitY.x, 0.0f);
    EXPECT_FLOAT_EQ(Vector3::UnitY.y, 1.0f);
}
