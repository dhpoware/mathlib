//-----------------------------------------------------------------------------
// Copyright (c) 2005-2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#if !defined(TEST_MAIN_H)
#define TEST_MAIN_H

#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "mathlib.h"
#include "collision.h"

extern void PrintVector(const char *label, const Vector2 &v);
extern void PrintVector(const char *label, const Vector3 &v);
extern void PrintMatrix(const char *label, const Matrix4 &m);
extern void PrintQuaternion(const char *label, const Quaternion &q);
extern void PrintPlane(const char *label, const Plane &p);
extern void PrintVectors(const Vector2 &result, const Vector2 &expected);
extern void PrintVectors(const Vector3 &result, const Vector3 &expected);
extern void PrintMatrices(const Matrix4 &result, const Matrix4 &expected);
extern void PrintQuaternions(const Quaternion &result, const Quaternion &expected);
extern void PrintPlanes(const Plane &result, const Plane &expected);

extern void TestMathCore();
extern void TestMathCollision();

#endif