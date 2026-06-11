
/************************************************************************|
|							   MathConfig.h			    			     |
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

#if SPROUT_MATH_DIRECTX

#include <Math/Vectors/DirectMath/Vector2_DX.h>
#include <Math/Vectors/DirectMath/Vector3_DX.h>

namespace SproutEngine::Maths
{
    using Vector2 = SPROUT_VECTOR2_DX;
    using Vector3 = SPROUT_VECTOR3_DX;
}

#elif SPROUT_MATH_GLM

#include <Math/Vectors/GLMath/Vector2_GLM.h>

namespace SproutEngine::Maths
{
    using Vector2 = SPROUT_VECTOR2_GLM;
}

#else
#error "No math backend selected"
#endif