#include "global.h"

#define Math3D_PlaneVsPlaneNewLine func_80179B94
#define Math3D_LineSegMakePerpLineSeg func_80179798
#define Math3D_Vec3f_Cross Math3D_CrossProduct
#define Math3D_Plane func_8017B9D8
#define Math3D_TriLineIntersect func_8017D404
#define Math3D_CylOutsideCylDist Math3D_ColCylinderCylinderAmountAndDistance
#define Math3D_CylOutsideCyl Math3D_ColCylinderCylinderAmount
#define Math3D_SphVsCylOverlapCenterDist Math3D_ColSphereCylinderDistanceAndAmount
#define Math3D_CylTriVsIntersect Math3D_ColCylinderTri
#define Math3D_CylVsTri func_8017F1A0
#define Math3D_SphVsSph Math3D_SphVsSph
#define Math3D_SphVsSphOverlap Math3D_ColSphereSphereIntersect
#define Math3D_SphVsSphOverlapCenter Math3D_ColSphereSphereIntersectAndDistance
#define Math3D_SphVsCylOverlapDist Math3D_ColSphereCylinderDistance
#define Math3D_CylVsLineSeg func_8017E350
#define Math3D_TriVsSphIntersect Math3D_ColSphereTri
#define Math3D_PointOnInfiniteLine Math3D_ScaleAndAdd
#define Math3D_LineSplitRatio Math3D_Lerp
#define Math3D_PlaneVsPlaneVsLineClosestPoint func_80179D74
#define Math3D_PointInCyl func_8017E294
#define Math3D_Cos Math3D_Parallel
#define Math3D_CosOut Math3D_AngleBetweenVectors
#define Math3D_Vec3fReflect func_80179F64
#define Math3D_PointInSquare2D Math3D_XZBoundCheck
#define Math3D_Dist1DSq Math3D_XZLengthSquared
#define Math3D_Dist1D Math3D_XZLength
#define Math3D_Dist2DSq Math3D_XZDistanceSquared
#define Math3D_Dist2D Math3D_XZDistance
#define Math3D_Vec3fMagnitudeSq Math3D_LengthSquared
#define Math3D_Vec3fDistSq Math3D_Vec3fDistSq
#define Math3D_Vec3f_DistXYZ Math3D_Distance
#define Math3D_DistXYZ16toF Math3D_DistanceS
#define Math3D_RotateXZPlane func_8017B7F8
#define Math3D_DefPlane Math3D_UnitNormalVector
#define Math3D_PlaneF Math3D_SignedDistanceFromPlane
#define Math3D_Plane func_8017B9D8
#define Math3D_DistPlaneToPos Math3D_DistPlaneToPos
#define Math3D_TriChkPointParaYImpl Math3D_TriChkPointParaYDist
#define Math3D_TriChkPointParaYDeterminate func_8017BD98
#define Math3D_TriChkPointParaYSlopedY func_8017BDE0
#define Math3D_TriChkPointParaY func_8017BF8C
#define Math3D_TriChkPointParaYDist_ func_8017C17C
#define Math3D_TriChkPointParaYImplNoCheckRange func_8017C1F0
#define Math3D_TriChkPointParaYNoRangeCheckIntersectInsideTri Math3D_TriChkPointParaYIntersectInsideTri2
#define Math3D_TriChkPointParaXImpl Math3D_TriChkPointParaXDist
#define Math3D_TriChkPointParaXDeterminate func_8017C808
#define Math3D_TriChkPointParaX func_8017C904
#define Math3D_TriChkLineSegParaXDist func_8017CB08
#define Math3D_TriChkPointParaZImpl Math3D_TriChkLineSegParaZDist
#define Math3D_TriChkPointParaZDeterminate func_8017CEA8
#define Math3D_TriChkPointParaZ func_8017CFA4
#define Math3D_TriChkLineSegParaZDist_ func_8017D1AC
#define Math3D_LineSegFindPlaneIntersect func_8017D220
#define Math3D_TriLineIntersect func_8017D404
#define Math3D_TriNorm Math3D_TriSetCoords
#define Math3D_PointInSph Math3D_IsPointInSphere
#define Math3D_PointDistToLine2D_ func_8017D814
#define Math3D_Vec3fMagnitudeSq Math3D_LengthSquared
#define Math3D_LineClosestToPoint func_80179A44

f32 Math3D_Normalize(Vec3f* vec) {
    f32 magnitude = Math3D_Vec3fMagnitude(vec);

    if (IS_ZERO(magnitude)) {
        return 0.0f;
    }

    vec->x *= 1.0f / magnitude;
    vec->y *= 1.0f / magnitude;
    vec->z *= 1.0f / magnitude;
    return magnitude;
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_PlaneVsLineSegClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB,
                                      f32 planeBC, f32 planeBDist, Vec3f* linePointA, Vec3f* linePointB,
                                      Vec3f* closestPoint) {
    static InfiniteLine planeIntersectLine;
    static Linef planeIntersectSeg;

    Vec3f sp34; // unused

    if (!Math3D_PlaneVsPlaneNewLine(planeAA, planeAB, planeAC, planeADist, planeBA, planeBB, planeBC, planeBDist,
                                    &planeIntersectLine)) {
        // The planes are parallel
        return false;
    }

    // create a line segment on the plane.
    Math_Vec3f_Copy(&planeIntersectSeg.a, &planeIntersectLine.point);
    planeIntersectSeg.b.x = (planeIntersectLine.dir.x * 100.0f) + planeIntersectLine.point.x;
    planeIntersectSeg.b.y = (planeIntersectLine.dir.y * 100.0f) + planeIntersectLine.point.y;
    planeIntersectSeg.b.z = (planeIntersectLine.dir.z * 100.0f) + planeIntersectLine.point.z;

    // closestPoint is a point on planeIntersect, sp34 is a point on linePointA, linePointB
    if (!Math3D_LineSegMakePerpLineSeg(&planeIntersectSeg.a, &planeIntersectSeg.b, linePointA, linePointB, closestPoint,
                                       &sp34)) {
        return false;
    }
    return true;
}
#else
// static InfiniteLine planeIntersectLine;
// static Linef planeIntersectSeg;
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_PlaneVsLineSegClosestPoint.s")
#endif

#ifdef NON_MATCHING
s32 Math3D_LineSegMakePerpLineSeg(Vec3f* lineAPointA, Vec3f* lineAPointB, Vec3f* lineBPointA, Vec3f* lineBPointB,
                                  Vec3f* lineAIntersect, Vec3f* lineBIntersect) {
    f32 sp5C;
    f32 sp50;
    f32 sp4C;
    f32 sp30;
    f32 temp_f0_4;
    f32 temp_f18;
    Vec3f lineADiff;
    Vec3f lineBDiff;
    Vec3f lineABPointADiff;
    f32 t;
    f32 t2;
    f32 tempf2;
    f32 tempf3;
    f32 tempf4;
    f32 tempf5;

    lineADiff.x = lineAPointB->x - lineAPointA->x;
    lineADiff.y = lineAPointB->y - lineAPointA->y;
    lineADiff.z = lineAPointB->z - lineAPointA->z;
    lineBDiff.x = lineBPointB->x - lineBPointA->x;
    lineBDiff.y = lineBPointB->y - lineBPointA->y;
    lineBDiff.z = lineBPointB->z - lineBPointA->z;

    if (IS_ZERO(SQXYZ(lineBDiff))) {
        return false;
    }
    sp5C = DOTXYZ(lineADiff, lineBDiff) * (1.0f / SQXYZ(lineBDiff));

    lineABPointADiff.x = lineAPointA->x - lineBPointA->x;
    lineABPointADiff.y = lineAPointA->y - lineBPointA->y;
    lineABPointADiff.z = lineAPointA->z - lineBPointA->z;

    // most reordering is here.
    temp_f18 = DOTXYZ(lineABPointADiff, lineBDiff) * (1.0f / SQXYZ(lineBDiff));

    sp4C = lineADiff.x - (lineBDiff.x * sp5C);
    sp50 = lineADiff.y - (lineBDiff.y * sp5C);
    sp30 = lineADiff.z - (lineBDiff.z * sp5C);

    if (IS_ZERO(SQ(sp4C) + SQ(sp50) + SQ(sp30))) {
        return false;
    }

    t = SQ(sp4C) + SQ(sp50) + SQ(sp30);
    temp_f0_4 = -((sp4C * (lineABPointADiff.x - (lineBDiff.x * temp_f18))) +
                  (sp50 * (lineABPointADiff.y - (lineBDiff.y * temp_f18))) +
                  (sp30 * (lineABPointADiff.z - (lineBDiff.z * temp_f18)))) /
                t;

    lineAIntersect->x = lineAPointA->x + (lineADiff.x * temp_f0_4);
    lineAIntersect->y = lineAPointA->y + (lineADiff.y * temp_f0_4);
    lineAIntersect->z = lineAPointA->z + (lineADiff.z * temp_f0_4);

    lineBIntersect->x = (lineBDiff.x * (temp_f18 + (temp_f0_4 * sp5C))) + lineBPointA->x;
    lineBIntersect->y = (lineBDiff.y * (temp_f18 + (temp_f0_4 * sp5C))) + lineBPointA->y;
    lineBIntersect->z = (lineBDiff.z * (temp_f18 + (temp_f0_4 * sp5C))) + lineBPointA->z;
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_80179798.s")
#endif

f32 Math3D_LineClosestToPoint(Linef* line, Vec3f* pos, Vec3f* closestPoint) {
    f32 dirVectorSize = Math3D_Vec3fMagnitudeSq(&line->b);
    f32 t;

    if (IS_ZERO(dirVectorSize)) {
        Math_Vec3f_Copy(closestPoint, pos);
    }

    t = (((pos->x - line->a.x) * line->b.x) + ((pos->y - line->a.y) * line->b.y) + ((pos->z - line->a.z) * line->b.z)) /
        dirVectorSize;
    closestPoint->x = (line->b.x * t) + line->a.x;
    closestPoint->y = (line->b.y * t) + line->a.y;
    closestPoint->z = (line->b.z * t) + line->a.z;

    return t;
}

#define Math3D_FindPointOnPlaneIntersect func_80179B34
void Math3D_FindPointOnPlaneIntersect(f32 planeAAxis1Norm, f32 planeAAxis2Norm, f32 planeBAxis1Norm,
                                      f32 planeBAxis2Norm, f32 axis3Direction, f32 planeADist, f32 planeBDist,
                                      f32* axis1Point, f32* axis2Point) {
    *axis1Point = ((planeAAxis2Norm * planeBDist) - (planeBAxis2Norm * planeADist)) / axis3Direction;
    *axis2Point = ((planeBAxis1Norm * planeADist) - (planeAAxis1Norm * planeBDist)) / axis3Direction;
}

#define Math3D_PlaneVsPlaneNewLine func_80179B94
s32 Math3D_PlaneVsPlaneNewLine(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB,
                               f32 planeBC, f32 planeBDist, InfiniteLine* intersect) {
    char pad[4];
    Vec3f planeANormal;
    Vec3f planeBNormal;
    f32 dirX;
    f32 dirY;
    f32 dirZ;

    VEC_SET(planeANormal, planeAA, planeAB, planeAC);
    VEC_SET(planeBNormal, planeBA, planeBB, planeBC);

    Math3D_Vec3f_Cross(&planeANormal, &planeBNormal, &intersect->dir);

    if (IS_ZERO(intersect->dir.x) && IS_ZERO(intersect->dir.y) && IS_ZERO(intersect->dir.z)) {
        // planes are parallel
        return false;
    }

    dirX = fabsf(intersect->dir.x);
    dirY = fabsf(intersect->dir.y);
    dirZ = fabsf(intersect->dir.z);

    if ((dirX >= dirY) && (dirX >= dirZ)) {
        Math3D_FindPointOnPlaneIntersect(planeAB, planeAC, planeBB, planeBC, intersect->dir.x, planeADist, planeBDist,
                                         &intersect->point.y, &intersect->point.z);
        intersect->point.x = 0.0f;
    } else if ((dirY >= dirX) && (dirY >= dirZ)) {
        Math3D_FindPointOnPlaneIntersect(planeAC, planeAA, planeBC, planeBA, intersect->dir.y, planeADist, planeBDist,
                                         &intersect->point.z, &intersect->point.x);
        intersect->point.y = 0.0f;
    } else {
        Math3D_FindPointOnPlaneIntersect(planeAA, planeAB, planeBA, planeBB, intersect->dir.z, planeADist, planeBDist,
                                         &intersect->point.x, &intersect->point.y);
        intersect->point.z = 0.0f;
    }
    return true;
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_PlaneVsPlaneVsLineClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA,
                                          f32 planeBB, f32 planeBC, f32 planeBDist, Vec3f* point, Vec3f* closestPoint) {
    static Linef planeIntersect;

    if (!Math3D_PlaneVsPlaneNewLine(planeAA, planeAB, planeAC, planeADist, planeBA, planeBB, planeBC, planeBDist,
                                    (InfiniteLine*)&planeIntersect)) {
        return false;
    }
    Math3D_LineClosestToPoint(&planeIntersect, point, closestPoint);
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_80179D74.s")
#endif

void Math3D_PointOnInfiniteLine(Vec3f* v0, Vec3f* dir, f32 dist, Vec3f* ret) {
    ret->x = (dir->x * dist) + v0->x;
    ret->y = (dir->y * dist) + v0->y;
    ret->z = (dir->z * dist) + v0->z;
}

void Math3D_LineSplitRatio(Vec3f* v0, Vec3f* v1, f32 ratio, Vec3f* ret) {
    Vec3f diff;

    Math_Vec3f_Diff(v1, v0, &diff);
    Math3D_PointOnInfiniteLine(v0, &diff, ratio, ret);
}

/**
 * Calculates the cosine between vectors `a` and `b`
 */
f32 Math3D_Cos(Vec3f* a, Vec3f* b) {
    f32 ret;

    Math3D_CosOut(a, b, &ret);
    return ret;
}

/**
 * Calculates the cosine between vectors `a` and `b` and places the result in `ret`
 * returns true if the cosine cannot be calculated because the product of the magnitudes is zero
 */
s32 Math3D_CosOut(Vec3f* a, Vec3f* b, f32* dst) {
    f32 magProduct = Math3D_Vec3fMagnitude(a) * Math3D_Vec3fMagnitude(b);

    if (IS_ZERO(magProduct)) {
        *dst = 0.0f;
        return true;
    }
    *dst = ((a->x * b->x) + (a->y * b->y) + (a->z * b->z)) / magProduct;
    return false;
}

void Math3D_Vec3fReflect(Vec3f* vec, Vec3f* normal, Vec3f* reflVec) {
    f32 normScaleY;
    Vec3f negVec;
    f32 normScaleZ;
    f32 normScaleX;
    f32 vecDotNorm;

    negVec.x = vec->x * -1.0f;
    negVec.y = vec->y * -1.0f;
    negVec.z = vec->z * -1.0f;

    vecDotNorm = Math3D_Cos(&negVec, normal);

    normScaleX = normal->x * vecDotNorm;
    normScaleY = normal->y * vecDotNorm;
    normScaleZ = normal->z * vecDotNorm;

    reflVec->x = ((normScaleX + vec->x) + (normScaleX + vec->x)) + negVec.x;
    reflVec->y = ((normScaleY + vec->y) + (normScaleY + vec->y)) + negVec.y;
    reflVec->z = ((normScaleZ + vec->z) + (normScaleZ + vec->z)) + negVec.z;
}


s32 Math3D_PointInSquare2D(f32 upperLeftX, f32 lowerRightX, f32 upperLeftY, f32 lowerRightY, f32 x, f32 y) {
    if (x >= upperLeftX && x <= lowerRightX && y >= upperLeftY && y <= lowerRightY) {
        return true;
    }
    return false;
}

s32 func_8017A09C(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 phi_f12;
    f32 phi_f14;

    if (arg0->x < arg1->x) {
        phi_f12 = arg0->x;
        phi_f14 = arg1->x;
    } else {
        phi_f12 = arg1->x;
        phi_f14 = arg0->x;
    }

    if (arg2->x < phi_f12) {
        phi_f12 = arg2->x;
    } else if (phi_f14 < arg2->x) {
        phi_f14 = arg2->x;
    }

    if (arg3 < (phi_f12 - arg5) || (phi_f14 + arg5) < arg3) {
        return 0;
    }
    if (arg0->y < arg1->y) {
        phi_f12 = arg0->y;
        phi_f14 = arg1->y;
    } else {
        phi_f12 = arg1->y;
        phi_f14 = arg0->y;
    }
    if (arg2->y < phi_f12) {
        phi_f12 = arg2->y;
    } else if (phi_f14 < arg2->y) {
        phi_f14 = arg2->y;
    }

    if (arg4 < (phi_f12 - arg5) || arg4 > (phi_f14 + arg5)) {
        return 0;
    }
    return 1;
}

s32 func_8017A1D0(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 phi_f12;
    f32 phi_f14;

    if (arg0->z < arg1->z) {
        phi_f12 = arg0->z;
        phi_f14 = arg1->z;
    } else {
        phi_f12 = arg1->z;
        phi_f14 = arg0->z;
    }

    if (arg2->z < phi_f12) {
        phi_f12 = arg2->z;
    } else if (phi_f14 < arg2->z) {
        phi_f14 = arg2->z;
    }

    if (arg4 < (phi_f12 - arg5) || (phi_f14 + arg5) < arg4) {
        return 0;
    }

    if (arg0->y < arg1->y) {
        phi_f12 = arg0->y;
        phi_f14 = arg1->y;
    } else {
        phi_f12 = arg1->y;
        phi_f14 = arg0->y;
    }

    if (arg2->y < phi_f12) {
        phi_f12 = arg2->y;
    } else if (phi_f14 < arg2->y) {
        phi_f14 = arg2->y;
    }

    if (arg3 < (phi_f12 - arg5) || (phi_f14 + arg5) < arg3) {
        return 0;
    }
    return 1;
}

s32 func_8017A304(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 phi_f12;
    f32 phi_f14;

    if (arg0->x < arg1->x) {
        phi_f12 = arg0->x;
        phi_f14 = arg1->x;
    } else {
        phi_f12 = arg1->x;
        phi_f14 = arg0->x;
    }

    if (arg2->x < phi_f12) {
        phi_f12 = arg2->x;
    } else if (phi_f14 < arg2->x) {
        phi_f14 = arg2->x;
    }

    if (arg4 < (phi_f12 - arg5) || (phi_f14 + arg5) < arg4) {
        return 0;
    }

    if (arg0->z < arg1->z) {
        phi_f12 = arg0->z;
        phi_f14 = arg1->z;
    } else {
        phi_f12 = arg1->z;
        phi_f14 = arg0->z;
    }

    if (arg2->z < phi_f12) {
        phi_f12 = arg2->z;
    } else if (phi_f14 < arg2->z) {
        phi_f14 = arg2->z;
    }

    if (arg3 < (phi_f12 - arg5) || (phi_f14 + arg5) < arg3) {
        return 0;
    }
    return 1;
}

// Math3D_SphCubeVsTriCube
s32 func_8017A438(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4) {
    f32 phi_f0;
    f32 phi_f2;

    if (arg0->x < arg1->x) {
        phi_f0 = arg0->x;
        phi_f2 = arg1->x;
    } else {
        phi_f0 = arg1->x;
        phi_f2 = arg0->x;
    }

    if (arg2->x < phi_f0) {
        phi_f0 = arg2->x;
    } else if (phi_f2 < arg2->x) {
        phi_f2 = arg2->x;
    }

    if (arg3->x < (phi_f0 - arg4) || (phi_f2 + arg4) < arg3->x) {
        return 0;
    }

    if (arg0->z < arg1->z) {
        phi_f0 = arg0->z;
        phi_f2 = arg1->z;
    } else {
        phi_f0 = arg1->z;
        phi_f2 = arg0->z;
    }

    if (arg2->z < phi_f0) {
        phi_f0 = arg2->z;
    } else if (phi_f2 < arg2->z) {
        phi_f2 = arg2->z;
    }

    if (arg3->z < (phi_f0 - arg4) || (phi_f2 + arg4) < arg3->z) {
        return 0;
    }

    if (arg0->y < arg1->y) {
        phi_f0 = arg0->y;
        phi_f2 = arg1->y;
    } else {
        phi_f0 = arg1->y;
        phi_f2 = arg0->y;
    }

    if (arg2->y < phi_f0) {
        phi_f0 = arg2->y;
    } else if (phi_f2 < arg2->y) {
        phi_f2 = arg2->y;
    }

    if (arg3->y < (phi_f0 - arg4) || (phi_f2 + arg4) < arg3->y) {
        return 0;
    }
    return 1;
}

f32 Math3D_Dist1DSq(f32 a, f32 b) {
    return SQ(a) + SQ(b);
}

f32 Math3D_Dist1D(f32 a, f32 b) {
    return sqrtf(Math3D_Dist1DSq(a, b));
}

f32 Math3D_Dist2DSq(f32 x0, f32 y0, f32 x1, f32 y1) {
    return Math3D_Dist1DSq(x0 - x1, y0 - y1);
}

f32 Math3D_Dist2D(f32 x0, f32 y0, f32 x1, f32 y1) {
    return sqrtf(Math3D_Dist2DSq(x0, y0, x1, y1));
}

f32 Math3D_Vec3fMagnitudeSq(Vec3f* vec) {
    return SQ(vec->x) + SQ(vec->y) + SQ(vec->z);
}

f32 Math3D_Vec3fMagnitude(Vec3f* vec) {
    return sqrtf(Math3D_Vec3fMagnitudeSq(vec));
}

f32 Math3D_Vec3fDistSq(Vec3f* a, Vec3f* b) {
    Vec3f diff;

    Math_Vec3f_Diff(a, b, &diff);

    return Math3D_Vec3fMagnitudeSq(&diff);
}

f32 Math3D_Vec3f_DistXYZ(Vec3f* a, Vec3f* b) {
    return Math_Vec3f_DistXYZ(a, b);
}

f32 Math3D_DistXYZ16toF(Vec3s* a, Vec3f* b) {
    Vec3f diff;

    diff.x = a->x - b->x;
    diff.y = a->y - b->y;
    diff.z = a->z - b->z;

    return Math3D_Vec3fMagnitude(&diff);
}

/**
 * Gets the Z portion of the cross product of vectors `a - (`dx`,`dy`,z) and `b` - (`dx`,`dy`,z)
 */
f32 Math3D_Vec3fDiff_CrossZ(Vec3f* a, Vec3f* b, f32 dx, f32 dy) {
    return ((a->x - dx) * (b->y - dy)) - ((a->y - dy) * (b->x - dx));
}

/**
 * Gets the X portion of the cross product of vectors `a - (x,`dy`,`dz`) and `b` - (x,`dy`,`dz`)
 */
f32 Math3D_Vec3fDiff_CrossX(Vec3f* a, Vec3f* b, f32 dy, f32 dz) {
    return ((a->y - dy) * (b->z - dz)) - ((a->z - dz) * (b->y - dy));
}

/**
 * Gets the Y portion of the cross product of vectors `a - (`dx`,y,`dz`) and `b` - (`dx`,y,`dz`)
 */
f32 Math3D_Vec3fDiff_CrossY(Vec3f* a, Vec3f* b, f32 dz, f32 dx) {
    return ((a->z - dz) * (b->x - dx)) - ((a->x - dx) * (b->z - dz));
}

void Math3D_Vec3f_Cross(Vec3f* a, Vec3f* b, Vec3f* ret) {
    ret->x = (a->y * b->z) - (a->z * b->y);
    ret->y = (a->z * b->x) - (a->x * b->z);
    ret->z = (a->x * b->y) - (a->y * b->x);
}

#ifdef NON_MATCHING
// in-function static bss
void Math3D_SurfaceNorm(Vec3f* va, Vec3f* vb, Vec3f* vc, Vec3f* normal) {
    static Vec3f abDiff;
    static Vec3f acDiff;

    Math_Vec3f_Diff(vb, va, &abDiff);
    Math_Vec3f_Diff(vc, va, &acDiff);
    Math3D_Vec3f_Cross(&abDiff, &acDiff, normal);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_SurfaceNorm.s")
#endif

s32 Math3D_PointRelativeToCubeFaces(Vec3f* point, Vec3f* min, Vec3f* max) {
    s32 ret = 0;

    if (point->x > max->x) {
        ret = 1;
    } else if (point->x < min->x) {
        ret |= 2;
    }

    if (point->y > max->y) {
        ret |= 4;
    } else if (point->y < min->y) {
        ret |= 8;
    }

    if (point->z > max->z) {
        ret |= 0x10;
    } else if (point->z < min->z) {
        ret |= 0x20;
    }

    return ret;
}

s32 Math3D_PointRelativeToCubeEdges(Vec3f* point, Vec3f* min, Vec3f* max) {
    s32 ret = 0;

    if ((-min->x + max->y) < (-point->x + point->y)) {
        ret |= 1;
    }

    if ((-point->x + point->y) < (-max->x + min->y)) {
        ret |= 2;
    }

    if ((max->x + max->y) < (point->x + point->y)) {
        ret |= 4;
    }

    if ((point->x + point->y) < (min->x + min->y)) {
        ret |= 8;
    }

    if ((-min->z + max->y) < (-point->z + point->y)) {
        ret |= 0x10;
    }

    if ((-point->z + point->y) < (-max->z + min->y)) {
        ret |= 0x20;
    }

    if ((max->z + max->y) < (point->z + point->y)) {
        ret |= 0x40;
    }

    if ((point->z + point->y) < (min->z + min->y)) {
        ret |= 0x80;
    }

    if ((-min->z + max->x) < (-point->z + point->x)) {
        ret |= 0x100;
    }

    if ((-point->z + point->x) < (-max->z + min->x)) {
        ret |= 0x200;
    }

    if ((max->z + max->x) < (point->z + point->x)) {
        ret |= 0x400;
    }

    if ((point->z + point->x) < (min->z + min->x)) {
        ret |= 0x800;
    }
    return ret;
}

s32 Math3D_PointRelativeToCubeVertices(Vec3f* point, Vec3f* min, Vec3f* max) {
    s32 ret = 0;

    if ((max->x + max->y + max->z) < (point->x + point->y + point->z)) {
        ret = 1;
    }

    if ((-min->x + max->y + max->z) < (-point->x + point->y + point->z)) {
        ret |= 2;
    }

    if ((-min->x + max->y - min->z) < (-point->x + point->y - point->z)) {
        ret |= 4;
    }

    if ((max->x + max->y - min->z) < (point->x + point->y - point->z)) {
        ret |= 8;
    }

    if ((max->x - min->y + max->z) < (point->x - point->y + point->z)) {
        ret |= 0x10;
    }

    //! @bug: The next 2 conditions are the same check.
    if ((-min->x - min->y + max->z) < (-point->x - point->y + point->z)) {
        ret |= 0x20;
    }

    if ((-min->x - min->y + max->z) < (-point->x - point->y + point->z)) {
        ret |= 0x40;
    }

    if ((-min->x - min->y - min->z) < (-point->x - point->y - point->z)) {
        ret |= 0x80;
    }
    return ret;
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_LineVsCube(Vec3f* min, Vec3f* max, Vec3f* a, Vec3f* b) {
    static Vec3f triVtx0;
    static Vec3f triVtx1;
    static Vec3f triVtx2;
    static Vec3f intersectPoint;

    s32 flags[2];

    flags[0] = flags[1] = 0;
    flags[0] = Math3D_PointRelativeToCubeFaces(a, min, max);
    if (!flags[0]) {
        return true;
    }

    flags[1] = Math3D_PointRelativeToCubeFaces(b, min, max);
    if (!flags[1]) {
        return true;
    }

    if (flags[0] & flags[1]) {
        return false;
    }

    flags[0] |= (Math3D_PointRelativeToCubeEdges(a, min, max) << 8);
    flags[1] |= (Math3D_PointRelativeToCubeEdges(b, min, max) << 8);
    if (flags[0] & flags[1]) {
        return false;
    }

    flags[0] |= (Math3D_PointRelativeToCubeVertices(a, min, max) << 0x18);
    flags[1] |= (Math3D_PointRelativeToCubeVertices(b, min, max) << 0x18);
    if (flags[0] & flags[1]) {
        return false;
    }

    // face 1
    triVtx0.x = min->x;
    triVtx0.y = min->y;
    triVtx0.z = min->z;
    triVtx1.x = min->x;
    triVtx1.y = min->y;
    triVtx1.z = max->z;
    triVtx2.x = min->x;
    triVtx2.y = max->y;
    triVtx2.z = max->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, -1.0f, 0.0f, 0.0f, min->x, a, b, &intersectPoint, 0)) {
        return true;
    }

    triVtx1.x = min->x;
    triVtx1.y = max->y;
    triVtx1.z = max->z;
    triVtx2.x = min->x;
    triVtx2.y = max->y;
    triVtx2.z = min->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, -1.0f, 0.0f, 0.0f, min->x, a, b, &intersectPoint, 0)) {
        return true;
    }

    // face 2
    triVtx0.x = min->x;
    triVtx0.y = max->y;
    triVtx0.z = max->z;
    triVtx1.x = min->x;
    triVtx1.y = min->y;
    triVtx1.z = max->z;
    triVtx2.x = max->x;
    triVtx2.y = max->y;
    triVtx2.z = max->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 0.0f, 1.0f, -max->z, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = max->y;
    triVtx0.z = max->z;
    triVtx2.x = max->x;
    //! @bug trVtx1.y should be triVtx2.y, prevents a tri on the cube from being checked.
    triVtx1.y = min->y;
    triVtx2.z = max->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 0.0f, 1.0f, -max->z, a, b, &intersectPoint, 0)) {
        return true;
    }

    // face 3
    triVtx0.x = min->x;
    triVtx0.y = max->y;
    triVtx0.z = min->z;
    triVtx2.x = min->x;
    triVtx2.y = max->y;
    triVtx2.z = max->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 1.0f, 0.0f, -max->y, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = max->y;
    triVtx0.z = max->z;
    triVtx1.x = min->x;
    triVtx1.y = max->y;
    triVtx1.z = min->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 1.0f, 0.0f, -max->y, a, b, &intersectPoint, 0)) {
        return true;
    }

    // face 4
    triVtx0.x = min->x;
    triVtx0.y = min->y;
    triVtx0.z = min->z;
    triVtx1.x = min->x;
    triVtx1.y = max->y;
    triVtx1.z = min->z;
    triVtx2.x = max->x;
    triVtx2.y = max->y;
    triVtx2.z = min->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 0.0f, -1.0f, min->z, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = max->y;
    triVtx0.z = min->z;
    triVtx1.x = max->x;
    triVtx1.y = min->y;
    triVtx1.z = min->z;

    // face 5
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, 0.0f, -1.0f, min->z, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = min->y;
    triVtx0.z = min->z;
    triVtx1.x = max->x;
    triVtx1.y = min->y;
    triVtx1.z = max->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, -1.0f, 0.0f, min->y, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = min->y;
    triVtx0.z = max->z;
    triVtx1.x = min->x;
    triVtx1.y = min->y;
    triVtx1.z = max->z;

    // face 6
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 0.0f, -1.0f, 0.0f, min->y, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = max->y;
    triVtx0.z = max->z;
    triVtx1.x = max->x;
    triVtx1.y = min->y;
    triVtx1.z = min->z;
    triVtx2.x = max->x;
    triVtx2.y = max->y;
    triVtx2.z = min->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 1.0f, 0.0f, 0.0f, -max->x, a, b, &intersectPoint, 0)) {
        return true;
    }
    triVtx0.x = max->x;
    triVtx0.y = min->y;
    triVtx0.z = max->z;
    triVtx1.x = max->x;
    triVtx1.y = min->y;
    triVtx1.z = min->z;
    if (Math3D_TriLineIntersect(&triVtx0, &triVtx1, &triVtx2, 1.0f, 0.0f, 0.0f, -max->x, a, b, &intersectPoint, 0)) {
        return true;
    }

    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_LineVsCube.s")
#endif

#ifdef NON_MATCHING
/**
 * Checks if a line segment with endpoints `a` and `b` intersect a cube
 */
// in-static bss
s32 Math3D_LineVsCubeShort(Vec3s* min, Vec3s* max, Vec3s* a, Vec3s* b) {
    static Vec3f D_801FBD20; // minF
    static Vec3f D_801FBD30; // maxF
    static Vec3f D_801FBD40; // aF
    static Vec3f D_801FBD50; // bF

    D_801FBD20.x = min->x;
    D_801FBD20.y = min->y;
    D_801FBD20.z = min->z;
    D_801FBD30.x = max->x;
    D_801FBD30.y = max->y;
    D_801FBD30.z = max->z;
    D_801FBD40.x = a->x;
    D_801FBD40.y = a->y;
    D_801FBD40.z = a->z;
    D_801FBD50.x = b->x;
    D_801FBD50.y = b->y;
    D_801FBD50.z = b->z;

    return Math3D_LineVsCube(&D_801FBD20, &D_801FBD30, &D_801FBD40, &D_801FBD50);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_8017B68C.s")
#endif

void Math3D_RotateXZPlane(Vec3f* pointOnPlane, s16 angle, f32* a, f32* c, f32* d) {
    *a = Math_SinS(angle) * 32767.0f;
    *c = Math_CosS(angle) * 32767.0f;
    *d = -((*a * pointOnPlane->x) + (*c * pointOnPlane->z));
}

#ifdef NON_MATCHING
// in-function static bss
void Math3D_DefPlane(Vec3f* va, Vec3f* vb, Vec3f* vc, f32* nx, f32* ny, f32* nz, f32* originDist) {
    static Vec3f normal;

    f32 normMagnitude;
    f32 normMagInv;

    Math3D_SurfaceNorm(va, vb, vc, &normal);
    normMagnitude = sqrtf(SQ(normal.x) + SQ(normal.y) + SQ(normal.z));
    if (!IS_ZERO(normMagnitude)) {
        normMagInv = 1.0f / normMagnitude;
        *nx = normal.x * normMagInv;
        *ny = normal.y * normMagInv;
        *nz = normal.z * normMagInv;
        *originDist = -((*nx * va->x) + (*ny * va->y) + (*nz * va->z));
    } else {
        *originDist = 0.0f;
        *nz = 0.0f;
        *ny = 0.0f;
        *nx = 0.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_UnitNormalVector.s")
#endif

f32 Math3D_PlaneF(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* pointOnPlane) {
    return (nx * pointOnPlane->x) + (ny * pointOnPlane->y) + (nz * pointOnPlane->z) + originDist;
}

f32 Math3D_Plane(Plane* plane, Vec3f* pointOnPlane) {
    return (plane->normal.x * pointOnPlane->x) + (plane->normal.y * pointOnPlane->y) +
           (plane->normal.z * pointOnPlane->z) + plane->originDist;
}

f32 Math3D_UDistPlaneToPos(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* p) {
    return fabsf(Math3D_DistPlaneToPos(nx, ny, nz, originDist, p));
}

f32 Math3D_DistPlaneToPos(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* p) {
    f32 normMagnitude = sqrtf(SQ(nx) + SQ(ny) + SQ(nz));

    if (IS_ZERO(normMagnitude)) {
        return 0.0f;
    }
    return Math3D_PlaneF(nx, ny, nz, originDist, p) / normMagnitude;
}

s32 Math3D_TriChkPointParaYImpl(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x, f32 detMax, f32 chkDist, f32 ny) {
    f32 detv0v1;
    f32 detv1v2;
    f32 detv2v0;
    f32 distToEdgeSq;
    f32 chkDistSq;

    // first check if the point is within range of the triangle.
    if (!func_8017A304(v0, v1, v2, z, x, chkDist)) {
        return false;
    }

    // check if the point is within `chkDist` units of any vertex of the triangle.
    chkDistSq = SQ(chkDist);
    if (SQ(v0->z - z) + SQ(v0->x - x) < chkDistSq || SQ(v1->z - z) + SQ(v1->x - x) < chkDistSq ||
        SQ(v2->z - z) + SQ(v2->x - x) < chkDistSq) {
        return true;
    }

    // Calculate the determinant of each face of the triangle to the point.
    // If all the of determinants are within abs(`detMax`), return true.
    if (((detMax >= (detv0v1 = ((v0->z - z) * (v1->x - x)) - ((v0->x - x) * (v1->z - z)))) &&
         (detMax >= (detv1v2 = ((v1->z - z) * (v2->x - x)) - ((v1->x - x) * (v2->z - z)))) &&
         (detMax >= (detv2v0 = ((v2->z - z) * (v0->x - x)) - ((v2->x - x) * (v0->z - z)))))) {
        return true;
    }

    if (((-detMax <= (detv0v1 = ((v0->z - z) * (v1->x - x)) - ((v0->x - x) * (v1->z - z)))) &&
         (-detMax <= (detv1v2 = ((v1->z - z) * (v2->x - x)) - ((v1->x - x) * (v2->z - z)))) &&
         (-detMax <= (detv2v0 = ((v2->z - z) * (v0->x - x)) - ((v2->x - x) * (v0->z - z)))))) {
        return true;
    }

    if (fabsf(ny) > 0.5f && chkDistSq > 0.0f) {
        // Do a check on each face of the triangle, if the point is within `chkDist` units return true.
        if ((func_8017DA24(z, x, v0, v1, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017DA24(z, x, v1, v2, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017DA24(z, x, v2, v0, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
    }
    return 0;
}

s32 Math3D_TriChkPointParaYDeterminate(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x, f32 detMax, f32 ny) {
    return Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, detMax, 1.0f, ny);
}

s32 Math3D_TriChkPointParaYSlopedY(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x) {
    return Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 300.0f, 1.0f, 0.6f);
}

s32 Math3D_TriChkPointParaYIntersectDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
                                         f32 x, f32* yIntersect, f32 chkDist) {
    if (IS_ZERO(ny)) {
        return false;
    }
    if (Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 300.0f, chkDist, ny)) {
        *yIntersect = (f32)((((-nx * x) - (nz * z)) - originDist) / ny);
        return true;
    }
    return false;
}


s32 Math3D_TriChkPointParaYIntersectInsideTri(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist,
                                              f32 z, f32 x, f32* yIntersect, f32 chkDist) {
    if (IS_ZERO(ny)) {
        return false;
    }
    if (Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 0.0f, chkDist, ny)) {
        *yIntersect = (f32)((((-nx * x) - (nz * z)) - originDist) / ny);
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaY(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 ny, f32 z, f32 x) {
    if (IS_ZERO(ny)) {
        return false;
    }
    if (Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 300.0f, 1.0f, ny)) {
        return true;
    }
    return false;
}

s32 Math3D_TriChkLineSegParaYIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
                                       f32 x, f32* yIntersect, f32 y0, f32 y1) {
    f32 pointADist;
    f32 pointBDist;
    Vec3f planePos;

    if (IS_ZERO(ny)) {
        return false;
    }

    planePos.x = x;
    planePos.y = y0;
    planePos.z = z;

    pointADist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);
    planePos.y = y1;
    pointBDist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);

    if (((pointADist > 0.0f) && (pointBDist > 0.0f)) || ((pointADist < 0.0f) && (pointBDist < 0.0f))) {
        return false;
    }
    if (Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 300.0f, 1.0f, ny)) {
        *yIntersect = (((-nx * x) - (nz * z)) - originDist) / ny;
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaYDist_(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 z, f32 x, f32 chkDist) {
    if (IS_ZERO(plane->normal.y)) {
        return false;
    }
    if (Math3D_TriChkPointParaYImpl(v0, v1, v2, z, x, 0.0f, chkDist, plane->normal.y)) {
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaYImplNoCheckRange(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x, f32 detMax, f32 chkDist,
                                            f32 ny) {
    f32 detv0v1;
    f32 detv1v2;
    f32 detv2v0;
    f32 distToEdgeSq;
    f32 chkDistSq;

    // check if the point is within `chkDist` units of any vertex of the triangle.
    chkDistSq = SQ(chkDist);
    if (SQ(v0->z - z) + SQ(v0->x - x) < chkDistSq || SQ(v1->z - z) + SQ(v1->x - x) < chkDistSq ||
        SQ(v2->z - z) + SQ(v2->x - x) < chkDistSq) {
        return true;
    }

    // Calculate the determinant of each face of the triangle to the point.
    // If all the of determinants are within abs(`detMax`), return true.
    if (((detMax >= (detv0v1 = ((v0->z - z) * (v1->x - x)) - ((v0->x - x) * (v1->z - z)))) &&
         (detMax >= (detv1v2 = ((v1->z - z) * (v2->x - x)) - ((v1->x - x) * (v2->z - z)))) &&
         (detMax >= (detv2v0 = ((v2->z - z) * (v0->x - x)) - ((v2->x - x) * (v0->z - z)))))) {
        return 1;
    }
    if (((-detMax <= (detv0v1 = ((v0->z - z) * (v1->x - x)) - ((v0->x - x) * (v1->z - z)))) &&
         (-detMax <= (detv1v2 = ((v1->z - z) * (v2->x - x)) - ((v1->x - x) * (v2->z - z)))) &&
         (-detMax <= (detv2v0 = ((v2->z - z) * (v0->x - x)) - ((v2->x - x) * (v0->z - z)))))) {
        return true;
    }

    if (fabsf(ny) > 0.5f && chkDistSq > 0.0f) {
        // Do a check on each face of the triangle, if the point is within `chkDist` units return true.
        if ((func_8017DA24(z, x, v0, v1, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017DA24(z, x, v1, v2, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017DA24(z, x, v2, v0, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
    }
    return 0;
}

s32 Math3D_TriChkPointParaYNoRangeCheckIntersectInsideTri(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz,
                                                          f32 originDist, f32 z, f32 x, f32* yIntersect, f32 chkDist) {
    if (IS_ZERO(ny)) {
        return false;
    }
    if (Math3D_TriChkPointParaYImplNoCheckRange(v0, v1, v2, z, x, 0.0f, chkDist, ny)) {
        *yIntersect = (f32)((((-nx * x) - (nz * z)) - originDist) / ny);
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaXImpl(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 detMax, f32 chkDist, f32 ny) {
    f32 detv0v1;
    f32 detv1v2;
    f32 detv2v0;
    f32 distToEdgeSq;
    f32 chkDistSq;

    // first check if the point is within range of the triangle.
    if (!func_8017A1D0(v0, v1, v2, y, z, chkDist)) {
        return false;
    }

    // check if the point is within `chkDist` units of any vertex of the triangle.
    chkDistSq = SQ(chkDist);
    if (SQ(v0->y - y) + SQ(v0->z - z) < chkDistSq || SQ(v1->y - y) + SQ(v1->z - z) < chkDistSq ||
        SQ(v2->y - y) + SQ(v2->z - z) < chkDistSq) {
        return true;
    }

    // Calculate the determinant of each face of the triangle to the point.
    // If all the of determinants are within abs(`detMax`), return true.
    if (((detMax >= (detv0v1 = ((v0->y - y) * (v1->z - z)) - ((v0->z - z) * (v1->y - y)))) &&
         (detMax >= (detv1v2 = ((v1->y - y) * (v2->z - z)) - ((v1->z - z) * (v2->y - y)))) &&
         (detMax >= (detv2v0 = ((v2->y - y) * (v0->z - z)) - ((v2->z - z) * (v0->y - y)))))) {
        return 1;
    }
    if (((-detMax <= (detv0v1 = ((v0->y - y) * (v1->z - z)) - ((v0->z - z) * (v1->y - y)))) &&
         (-detMax <= (detv1v2 = ((v1->y - y) * (v2->z - z)) - ((v1->z - z) * (v2->y - y)))) &&
         (-detMax <= (detv2v0 = ((v2->y - y) * (v0->z - z)) - ((v2->z - z) * (v0->y - y)))))) {
        return true;
    }

    if (fabsf(ny) > 0.5f && chkDistSq > 0.0f) {
        // Do a check on each face of the triangle, if the point is within `chkDist` units return true.
        if ((func_8017D91C(y, z, v0, v1, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017D91C(y, z, v1, v2, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
        if ((func_8017D91C(y, z, v2, v0, &distToEdgeSq) != 0) && (distToEdgeSq < chkDistSq)) {
            return 1;
        }
    }
    return 0;
}

s32 Math3D_TriChkPointParaXDeterminate(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 detMax, f32 nx) {
    return Math3D_TriChkPointParaXImpl(v0, v1, v2, y, z, detMax, 1.0f, nx);
}

s32 Math3D_TriChkPointParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
                                     f32 z, f32* xIntersect) {
    if (IS_ZERO(nx)) {
        return false;
    }

    if (Math3D_TriChkPointParaXImpl(v0, v1, v2, y, z, 300.0f, 1.0f, nx)) {
        *xIntersect = (((-ny * y) - (nz * z)) - originDist) / nx;
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaX(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 y, f32 z) {
    if (IS_ZERO(nx)) {
        return false;
    }
    if (Math3D_TriChkPointParaXImpl(v0, v1, v2, y, z, 300.0f, 1.0f, nx)) {
        return true;
    }
    return false;
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_TriChkLineSegParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
                                       f32 z, f32* xIntersect, f32 x0, f32 x1) {
    static Vec3f planePos;

    f32 pointADist;
    f32 pointBDist;

    if (IS_ZERO(nx)) {
        return false;
    }

    planePos.x = x0;
    planePos.y = y;
    planePos.z = z;
    pointADist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);

    planePos.x = x1;
    pointBDist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);

    if (((pointADist > 0.0f) && (pointBDist > 0.0f)) || ((pointADist < 0.0f) && (pointBDist < 0.0f))) {
        return false;
    }

    if (Math3D_TriChkPointParaXImpl(v0, v1, v2, y, z, 300.0f, 1.0f, nx)) {
        *xIntersect = (((-ny * y) - (nz * z)) - originDist) / nx;
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_TriChkLineSegParaXIntersect.s")
#endif

s32 Math3D_TriChkLineSegParaXDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 y, f32 z, f32 chkDist) {
    if (IS_ZERO(plane->normal.x)) {
        return false;
    }
    if (Math3D_TriChkPointParaXImpl(v0, v1, v2, y, z, 0.0f, chkDist, plane->normal.x)) {
        return true;
    }
    return false;
}

s32 Math3D_TriChkPointParaZImpl(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 x, f32 y, f32 detMax, f32 chkDist, f32 nz) {
    f32 detv0v1;
    f32 detv1v2;
    f32 detv2v0;
    f32 distToEdgeSq;
    f32 chkDistSq;

    if (!func_8017A09C(v0, v1, v2, x, y, chkDist)) {
        return false;
    }

    chkDistSq = SQ(chkDist);

    if (((SQ(x - v0->x) + SQ(y - v0->y)) < chkDistSq) || ((SQ(x - v1->x) + SQ(y - v1->y)) < chkDistSq) ||
        ((SQ(x - v2->x) + SQ(y - v2->y)) < chkDistSq)) {
        // Distance from any vertex to a point is less than chkDist
        return true;
    }

    if (((detMax >= (detv0v1 = ((v0->x - x) * (v1->y - y)) - ((v0->y - y) * (v1->x - x)))) &&
         (detMax >= (detv1v2 = ((v1->x - x) * (v2->y - y)) - ((v1->y - y) * (v2->x - x)))) &&
         (detMax >= (detv2v0 = ((v2->x - x) * (v0->y - y)) - ((v2->y - y) * (v0->x - x)))))) {
        return true;
    }

    if (((-detMax <= (detv0v1 = ((v0->x - x) * (v1->y - y)) - ((v0->y - y) * (v1->x - x)))) &&
         (-detMax <= (detv1v2 = ((v1->x - x) * (v2->y - y)) - ((v1->y - y) * (v2->x - x)))) &&
         (-detMax <= (detv2v0 = ((v2->x - x) * (v0->y - y)) - ((v2->y - y) * (v0->x - x)))))) {
        return true;
    }

    if (fabsf(nz) > 0.5f && chkDistSq > 0.0f) {

        if (func_8017D814(x, y, v0, v1, &distToEdgeSq) && (distToEdgeSq < chkDistSq)) {
            return true;
        }

        if (func_8017D814(x, y, v1, v2, &distToEdgeSq) && (distToEdgeSq < chkDistSq)) {
            return true;
        }

        if (func_8017D814(x, y, v2, v0, &distToEdgeSq) && (distToEdgeSq < chkDistSq)) {
            return true;
        }
    }

    return false;
}

s32 Math3D_TriChkPointParaZDeterminate(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 detMax, f32 nx) {
    return Math3D_TriChkPointParaZImpl(v0, v1, v2, y, z, detMax, 1.0f, nx);
}

s32 Math3D_TriChkPointParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x, f32 y,
                  f32* zIntersect) {
    if (IS_ZERO(nz)) {
        return 0;
    }

    if (Math3D_TriChkPointParaZImpl(v0, v1, v2, x, y, 300.0f, 1.0f, nz)) {
        *zIntersect = (((-nx * x) - (ny * y)) - originDist) / nz;
        return 1;
    }

    return 0;
}

s32 Math3D_TriChkPointParaZ(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 y, f32 z) {
    if (IS_ZERO(nx)) {
        return false;
    }
    if (Math3D_TriChkPointParaZImpl(v0, v1, v2, y, z, 300.0f, 1.0f, nx)) {
        return true;
    }
    return false;
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_TriChkLineSegParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x,
                                       f32 y, f32* zIntersect, f32 z0, f32 z1) {
    static Vec3f planePos;

    f32 pointADist;
    f32 pointBDist;

    if (IS_ZERO(nz)) {
        return false;
    }
    planePos.x = x;
    planePos.y = y;
    planePos.z = z0;
    pointADist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);

    planePos.z = z1;
    pointBDist = Math3D_PlaneF(nx, ny, nz, originDist, &planePos);
    if (((pointADist > 0.0f) && (pointBDist > 0.0f)) || ((pointADist < 0.0f) && (pointBDist < 0.0f))) {
        // points on the line segment are on the same side of the plane
        return false;
    }

    if (Math3D_TriChkPointParaXImpl(v0, v1, v2, x, y, 300.0f, 1.0f, nz)) {
        *zIntersect = (((-nx * x) - (ny * y)) - originDist) / nz;
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_TriChkLineSegParaZIntersect.s")
#endif

s32 Math3D_TriChkLineSegParaZDist_(Vec3f* v0, Vec3f* v1, Vec3f* v2, Plane* plane, f32 x, f32 y, f32 chkDist) {
    if (IS_ZERO(plane->normal.z)) {
        return false;
    }
    if (Math3D_TriChkPointParaZImpl(v0, v1, v2, x, y, 0.0f, chkDist, plane->normal.z)) {
        return true;
    }
    return false;
}

s32 Math3D_LineSegFindPlaneIntersect(f32 pointADist, f32 pointBDist, Vec3f* pointA, Vec3f* pointB, Vec3f* intersect) {
    f32 distDiff = pointADist - pointBDist;

    if (IS_ZERO(distDiff)) {
        // both points lie on the plane.
        *intersect = *pointB;
        return false;
    }

    if (pointADist == 0.0f) {
        // pointA is on the plane
        *intersect = *pointA;
    } else if (pointBDist == 0.0f) {
        // pointB is on the plane
        *intersect = *pointB;
    } else {
        // place the point at the intersection point.
        Math3D_LineSplitRatio(pointA, pointB, pointADist / distDiff, intersect);
    }
    return true;
}

s32 Math3D_LineSegVsPlane(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA, Vec3f* linePointB,
                          Vec3f* intersect, s32 fromFront) {
    f32 pointADist = Math3D_PlaneF(nx, ny, nz, originDist, linePointA);
    f32 pointBDist = Math3D_PlaneF(nx, ny, nz, originDist, linePointB);

    if ((pointADist * pointBDist) > 0.0f) {
        *intersect = *linePointB;
        return false;
    }

    if (fromFront && (pointADist < 0.0f) && (pointBDist > 0.0f)) {
        *intersect = *linePointB;
        return false;
    }

    return Math3D_LineSegFindPlaneIntersect(pointADist, pointBDist, linePointA, linePointB, intersect);
}

s32 Math3D_TriLineIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA,
                            Vec3f* linePointB, Vec3f* intersect, s32 fromFront) {

    if (!Math3D_LineSegVsPlane(nx, ny, nz, originDist, linePointA, linePointB, intersect, fromFront)) {
        return false;
    }

    if (((nx == 0.0f) || (Math3D_TriChkPointParaX(v0, v1, v2, nx, intersect->y, intersect->z))) &&
        ((ny == 0.0f) || (Math3D_TriChkPointParaY(v0, v1, v2, ny, intersect->z, intersect->x))) &&
        ((nz == 0.0f) || (Math3D_TriChkPointParaZ(v0, v1, v2, nz, intersect->x, intersect->y)))) {
        return true;
    }

    *intersect = *linePointB;
    return false;
}

void Math3D_TriNorm(TriNorm* tri, Vec3f* va, Vec3f* vb, Vec3f* vc) {
    tri->vtx[0] = *va;
    tri->vtx[1] = *vb;
    tri->vtx[2] = *vc;
    Math3D_DefPlane(va, vb, vc, &tri->plane.normal.x, &tri->plane.normal.y, &tri->plane.normal.z,
                    &tri->plane.originDist);
}

s32 Math3D_PointInSph(Sphere16* sphere, Vec3f* point) {
    if (Math3D_DistXYZ16toF(&sphere->center, point) < sphere->radius) {
        return true;
    }
    return false;
}

s32 Math3D_PointDistToLine2D(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* perpXOut, f32* perpYOut, f32* lineLenSq) {
    f32 perpendicularRatio;
    f32 xDiff = x2 - x1;
    f32 yDiff = y2 - y1;
    f32 distSq = SQ(xDiff) + SQ(yDiff);
    s32 ret = false;

    if (IS_ZERO(distSq)) {
        *lineLenSq = 0.0f;
        return false;
    }

    perpendicularRatio = ((x0 - x1) * xDiff + (y0 - y1) * yDiff) / distSq;
    if (perpendicularRatio >= 0.0f && perpendicularRatio <= 1.0f) {
        ret = true;
    }

    *perpXOut = (xDiff * perpendicularRatio) + x1;
    *perpYOut = (yDiff * perpendicularRatio) + y1;

    *lineLenSq = SQ(*perpXOut - x0) + SQ(*perpYOut - y0);
    return ret;
}

s32 func_8017D7C0(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lineLenSq) {
    f32 perpX;
    f32 perpY;

    return Math3D_PointDistToLine2D(x0, y0, x1, y1, x2, y2, &perpX, &perpY, lineLenSq);
}

s32 Math3D_PointDistToLine2D_(f32 x0, f32 y0, Vec3f* p1, Vec3f* p2, f32* lineLenSq) {
    f32 perpendicularRatio;
    f32 xDiff = p2->x - p1->x;
    f32 yDiff = p2->y - p1->y;
    f32 distSq = SQ(xDiff) + SQ(yDiff);
    f32 perpX;
    f32 perpY;
    s32 ret = false;

    if (IS_ZERO(distSq)) {
        *lineLenSq = 0.0f;
        return false;
    }

    perpendicularRatio = ((x0 - p1->x) * xDiff + (y0 - p1->y) * yDiff) / distSq;
    if (perpendicularRatio >= 0.0f && perpendicularRatio <= 1.0f) {
        ret = true;
    }
    perpX = (xDiff * perpendicularRatio) + p1->x;
    perpY = (yDiff * perpendicularRatio) + p1->y;
    *lineLenSq = SQ(perpX - x0) + SQ(perpY - y0);

    return ret;
}

s32 func_8017D91C(f32 y0, f32 z0, Vec3f* p1, Vec3f* p2, f32* lineLenSq) {
    f32 perpendicularRatio;
    f32 yDiff = p2->y - p1->y;
    f32 zDiff = p2->z - p1->z;
    f32 distSq = SQ(yDiff) + SQ(zDiff);
    f32 perpY;
    f32 perpZ;
    s32 ret = false;

    if (IS_ZERO(distSq)) {
        *lineLenSq = 0.0f;
        return false;
    }

    perpendicularRatio = ((y0 - p1->y) * yDiff + (z0 - p1->z) * zDiff) / distSq;
    if (perpendicularRatio >= 0.0f && perpendicularRatio <= 1.0f) {
        ret = true;
    }
    perpY = (yDiff * perpendicularRatio) + p1->y;
    perpZ = (zDiff * perpendicularRatio) + p1->z;
    *lineLenSq = SQ(perpY - y0) + SQ(perpZ - z0);

    return ret;
}

s32 func_8017DA24(f32 z0, f32 x0, Vec3f* p1, Vec3f* p2, f32* lineLenSq) {
    f32 perpendicularRatio;
    f32 zDiff = p2->z - p1->z;
    f32 xDiff = p2->x - p1->x;
    f32 distSq = SQ(zDiff) + SQ(xDiff);
    f32 perpZ;
    f32 perpX;
    s32 ret = false;

    if (IS_ZERO(distSq)) {
        *lineLenSq = 0.0f;
        return false;
    }

    perpendicularRatio = ((z0 - p1->z) * zDiff + (x0 - p1->x) * xDiff) / distSq;
    if (perpendicularRatio >= 0.0f && perpendicularRatio <= 1.0f) {
        ret = true;
    }
    perpZ = (zDiff * perpendicularRatio) + p1->z;
    perpX = (xDiff * perpendicularRatio) + p1->x;
    *lineLenSq = SQ(perpZ - z0) + SQ(perpX - x0);

    return ret;
}

#define Math3D_TriVsSphIntersect Math3D_ColSphereTri
#define Math3D_GetSphVsTriIntersectPoint func_8017DD34

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_LineVsSph(Sphere16* sphere, Linef* line) {
    static Vec3f sphLinePerpendicularPoint;

    Vec3f lineDiff;
    f32 temp_f0_2;
    f32 lineLenSq;

    if ((Math3D_PointInSph(sphere, &line->a)) || (Math3D_PointInSph(sphere, &line->b))) {
        // either point of the line is in the sphere.
        return true;
    }
    lineDiff.x = line->b.x - line->a.x;
    lineDiff.y = line->b.y - line->a.y;
    lineDiff.z = line->b.z - line->a.z;

    lineLenSq = SQ(lineDiff.x) + SQ(lineDiff.y) + SQ(lineDiff.z);
    if (IS_ZERO(lineLenSq)) {
        // line length is "0"
        return false;
    }
    temp_f0_2 = ((((sphere->center.x - line->a.x) * lineDiff.x) + ((sphere->center.y - line->a.y) * lineDiff.y)) +
                 ((sphere->center.z - line->a.z) * lineDiff.z)) /
                lineLenSq;
    if ((temp_f0_2 < 0.0f) || (temp_f0_2 > 1.0f)) {
        return false;
    }

    sphLinePerpendicularPoint.x = (lineDiff.x * temp_f0_2) + line->a.x;
    sphLinePerpendicularPoint.y = (lineDiff.y * temp_f0_2) + line->a.y;
    sphLinePerpendicularPoint.z = (lineDiff.z * temp_f0_2) + line->a.z;

    if (SQ(sphLinePerpendicularPoint.x - sphere->center.x) + SQ(sphLinePerpendicularPoint.y - sphere->center.y) +
            SQ(sphLinePerpendicularPoint.z - sphere->center.z) <=
        SQ((f32)sphere->radius)) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_LineVsSph.s")
#endif

#ifdef NON_MATCHING
// in-function static bss
void Math3D_GetSphVsTriIntersectPoint(Sphere16* sphere, TriNorm* tri, Vec3f* intersectPoint) {
    static Vec3f v0v1Center;
    static Vec3f sphereCenter;

    f32 dist;
    f32 splitRatio;

    v0v1Center.x = ((tri->vtx[0].x + tri->vtx[1].x) * 0.5f);
    v0v1Center.y = ((tri->vtx[0].y + tri->vtx[1].y) * 0.5f);
    v0v1Center.z = ((tri->vtx[0].z + tri->vtx[1].z) * 0.5f);
    sphereCenter.x = sphere->center.x;
    sphereCenter.y = sphere->center.y;
    sphereCenter.z = sphere->center.z;
    dist = Math3D_Vec3f_DistXYZ(&v0v1Center, &sphereCenter);
    // Distance from the sphere's center to the center of the line formed from v0->v1
    if (IS_ZERO(dist)) {
        intersectPoint->x = sphereCenter.x;
        intersectPoint->y = sphereCenter.y;
        intersectPoint->z = sphereCenter.z;
        return;
    }
    splitRatio = sphere->radius / dist;
    Math3D_LineSplitRatio(&sphereCenter, &v0v1Center, splitRatio, intersectPoint);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_8017DD34.s")
#endif

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_TriVsSphIntersect(Sphere16* sphere, TriNorm* tri, Vec3f* intersectPoint) {
    static Linef triTestLine;
    static Vec3f sphereCenter;
    static Vec3f sphPlanePos;

    f32 radius;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 planeDist;

    sphereCenter.x = sphere->center.x;
    sphereCenter.y = sphere->center.y;
    sphereCenter.z = sphere->center.z;
    radius = sphere->radius;

    if (!func_8017A438(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], &sphereCenter, radius)) {
        return false;
    }

    planeDist = Math3D_UDistPlaneToPos(tri->plane.normal.x, tri->plane.normal.y, tri->plane.normal.z,
                                       tri->plane.originDist, &sphereCenter);
    if (radius < planeDist) {
        // the point that lies within the plane of the triangle which is perpendicular to the sphere's center is more
        // than the radius of the sphere, the plane never crosses the sphere.
        return false;
    }

    // tests if any of the edges of the triangle are intersecting the sphere
    triTestLine.a = tri->vtx[0];
    triTestLine.b = tri->vtx[1];
    if (Math3D_LineVsSph(sphere, &triTestLine)) {
        Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
        return true;
    }

    triTestLine.a = tri->vtx[1];
    triTestLine.b = tri->vtx[2];
    if (Math3D_LineVsSph(sphere, &triTestLine)) {
        Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
        return true;
    }

    triTestLine.a = tri->vtx[2];
    triTestLine.b = tri->vtx[0];
    if (Math3D_LineVsSph(sphere, &triTestLine)) {
        Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
        return true;
    }

    nx = tri->plane.normal.x * planeDist;
    ny = tri->plane.normal.y * planeDist;
    nz = tri->plane.normal.z * planeDist;

    if (Math3D_PlaneF(tri->plane.normal.x, tri->plane.normal.y, tri->plane.normal.z, tri->plane.originDist,
                      &sphereCenter) > 0.0f) {
        sphPlanePos.x = sphereCenter.x - nx;
        sphPlanePos.y = sphereCenter.y - ny;
        sphPlanePos.z = sphereCenter.z - nz;
    } else {
        sphPlanePos.x = sphereCenter.x + nx;
        sphPlanePos.y = sphereCenter.y + ny;
        sphPlanePos.z = sphereCenter.z + nz;
    }

    if (fabsf(tri->plane.normal.y) > 0.5f) {
        if (Math3D_TriChkPointParaYDeterminate(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], sphPlanePos.z, sphPlanePos.x,
                                               0.0f, tri->plane.normal.y)) {
            Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
            return true;
        }
    } else if (fabsf(tri->plane.normal.x) > 0.5f) {
        if (Math3D_TriChkPointParaXDeterminate(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], sphPlanePos.y, sphPlanePos.z,
                                               0.0f, tri->plane.normal.x)) {
            Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
            return true;
        }
    } else if (Math3D_TriChkPointParaZDeterminate(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], sphPlanePos.x,
                                                  sphPlanePos.y, 0.0f, tri->plane.normal.z)) {
        Math3D_GetSphVsTriIntersectPoint(sphere, tri, intersectPoint);
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_ColSphereTri.s")
#endif

s32 Math3D_PointInCyl(Cylinder16* cyl, Vec3f* point) {
    f32 bottom;
    f32 top;
    f32 x = cyl->pos.x - point->x;
    f32 z = cyl->pos.z - point->z;

    bottom = (f32)cyl->pos.y + cyl->yShift;
    top = cyl->height + bottom;

    if ((SQ(x) + SQ(z)) < SQ(cyl->radius) && (bottom < point->y) && (point->y < top)) {
        return true;
    } else {
        return false;
    }
}

#ifdef NON_MATCHING
// fracA and fracB are init to 0 but this causes problems everywhere
s32 Math3D_CylVsLineSeg(Cylinder16* cyl, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersectA, Vec3f* intersectB) {
    Vec3f cylToPtA;
    Vec3f cylToPtB;
    Vec3f ptAToPtB;
    f32 fracA;
    f32 fracB;
    f32 fracBase;
    f32 zero = 0.0f;
    f32 pad;
    f32 cylRadiusSq;
    f32 radSqDiff;
    f32 distCent2;
    f32 dot2AB;
    s32 sideIntA;
    s32 sideIntB;
    s32 intBeyondA;
    s32 intBeyondB;
    s32 intFlags = 0;
    Vec3f intPts[4];
    s32 count;
    s32 i;

    if (Math3D_PointInCyl(cyl, linePointA) && Math3D_PointInCyl(cyl, linePointB)) {
        // both points are in the cylinder
        *intersectA = *linePointA;
        *intersectB = *linePointB;
        return 2;
    }

    cylToPtA.x = linePointA->x - cyl->pos.x;
    cylToPtA.y = linePointA->y - cyl->pos.y - cyl->yShift;
    cylToPtA.z = linePointA->z - cyl->pos.z;
    cylToPtB.x = linePointB->x - cyl->pos.x;
    cylToPtB.y = linePointB->y - cyl->pos.y - cyl->yShift;
    cylToPtB.z = linePointB->z - cyl->pos.z;
    Math_Vec3f_Diff(&cylToPtB, &cylToPtA, &ptAToPtB);
    cylRadiusSq = SQ(cyl->radius);

    /**
     * This section checks for intersections with the cylinder's base and top
     */
    if (!IS_ZERO(ptAToPtB.y)) {
        // fraction of length along AB to reach y = 0
        fracBase = -cylToPtA.y / ptAToPtB.y;
        if ((0.0f <= fracBase) && (fracBase <= 1.0f)) {
            f32 baseIntX = (ptAToPtB.x * fracBase) + cylToPtA.x;
            f32 baseIntZ = (ptAToPtB.z * fracBase) + cylToPtA.z;

            if (SQ(baseIntX) + SQ(baseIntZ) < cylRadiusSq) {
                // adds base intersection point to intPts and sets its flag
                intPts[0].x = cyl->pos.x + baseIntX;
                intPts[0].y = (f32)cyl->pos.y + cyl->yShift;
                intPts[0].z = cyl->pos.z + baseIntZ;
                intFlags |= 1;
            }
        }
        // fraction of length along AB to reach y = cyl->height
        fracA = (cyl->height - cylToPtA.y) / ptAToPtB.y;
        if ((0.0f <= fracA) && (fracA <= 1.0f)) {
            f32 topIntX = ptAToPtB.x * fracA + cylToPtA.x;
            f32 topIntZ = ptAToPtB.z * fracA + cylToPtA.z;

            if (SQ(topIntX) + SQ(topIntZ) < cylRadiusSq) {
                // adds top intersection point to intPts and sets its flag
                intPts[1].x = cyl->pos.x + topIntX;
                intPts[1].y = (f32)cyl->pos.y + cyl->yShift + cyl->height;
                intPts[1].z = cyl->pos.z + topIntZ;
                intFlags |= 2;
            }
        }
    }
    /**
     * This section finds the points of intersection of the infinite line containing AB with the side of the infinite
     * cylinder containing cyl. Intersection points beyond the bounds of the segment and cylinder are filtered out
     * afterward.
     */
    radSqDiff = SQXZ(cylToPtA) - cylRadiusSq;
    if (!IS_ZERO(2.0f * SQXZ(ptAToPtB))) {
        dot2AB = 2.0f * DOTXZ(ptAToPtB, cylToPtA);
        if (SQ(dot2AB) < 4.0f * SQXZ(ptAToPtB) * radSqDiff) {
            // Line's closest xz-approach is outside cylinder. No intersections.
            return 0;
        }
        if (SQ(dot2AB) - (4.0f * SQXZ(ptAToPtB) * radSqDiff) > zero) {
            sideIntA = sideIntB = 1;
        } else {
            // Line is tangent in xz-plane. At most 1 side intersection.
            sideIntA = 1;
            sideIntB = 0;
        }
        distCent2 = sqrtf(SQ(dot2AB) - (4.0f * SQXZ(ptAToPtB) * radSqDiff));
        if (sideIntA != 0) {
            // fraction of length along AB for side intersection closer to A
            fracA = (distCent2 - dot2AB) / (2.0f * SQXZ(ptAToPtB));
        }
        if (sideIntB != 0) {
            // fraction of length along AB for side intersection closer to B
            fracB = (-dot2AB - distCent2) / (2.0f * SQXZ(ptAToPtB));
        }
    } else if (!IS_ZERO(2.0f * DOTXZ(ptAToPtB, cylToPtA))) {
        // Used if the line segment is nearly vertical. Unclear what it's calculating.
        fracA = -radSqDiff / (2.0f * DOTXZ(ptAToPtB, cylToPtA));
        sideIntA = 1;
        sideIntB = 0;
    } else {
        return 0;
    }
    // checks for intersection points outside the bounds of the segment
    if (!sideIntB) {
        if (fracA < 0.0f || 1.0f < fracA) {
            return 0;
        }
    } else {
        intBeyondA = fracA < 0.0f || 1.0f < fracA;
        intBeyondB = fracB < 0.0f || 1.0f < fracB;
        if (intBeyondA && intBeyondB) {
            return 0;
        }
        if (intBeyondA) {
            sideIntA = 0;
        }
        if (intBeyondB) {
            sideIntB = 0;
        }
    }
    // checks for intersection points outside the bounds of the cylinder
    if ((sideIntA != 0) &&
        ((fracA * ptAToPtB.y + cylToPtA.y) < 0.0f || cyl->height < (fracA * ptAToPtB.y + cylToPtA.y))) {
        sideIntA = 0;
    }
    if ((sideIntB != 0) &&
        ((fracB * ptAToPtB.y + cylToPtA.y) < 0.0f || cyl->height < (fracB * ptAToPtB.y + cylToPtA.y))) {
        sideIntB = 0;
    }
    if (sideIntA == 0 && sideIntB == 0) {
        return 0;
    }
    // Adds intersection points to intPts and sets side A and side B flags
    if (sideIntA != 0 && sideIntB != 0) {
        intPts[2].x = (fracA * ptAToPtB.x + cylToPtA.x) + cyl->pos.x;
        intPts[2].y = (fracA * ptAToPtB.y + cylToPtA.y) + cyl->pos.y + cyl->yShift;
        intPts[2].z = (fracA * ptAToPtB.z + cylToPtA.z) + cyl->pos.z;
        intFlags |= 4;
        intPts[3].x = (fracB * ptAToPtB.x + cylToPtA.x) + cyl->pos.x;
        intPts[3].y = (fracB * ptAToPtB.y + cylToPtA.y) + cyl->pos.y + cyl->yShift;
        intPts[3].z = (fracB * ptAToPtB.z + cylToPtA.z) + cyl->pos.z;
        intFlags |= 8;
    } else if (sideIntA != 0) {
        intPts[2].x = (fracA * ptAToPtB.x + cylToPtA.x) + cyl->pos.x;
        intPts[2].y = (fracA * ptAToPtB.y + cylToPtA.y) + cyl->pos.y + cyl->yShift;
        intPts[2].z = (fracA * ptAToPtB.z + cylToPtA.z) + cyl->pos.z;
        intFlags |= 4;
    } else if (sideIntB != 0) {
        intPts[2].x = (fracB * ptAToPtB.x + cylToPtA.x) + cyl->pos.x;
        intPts[2].y = (fracB * ptAToPtB.y + cylToPtA.y) + cyl->pos.y + cyl->yShift;
        intPts[2].z = (fracB * ptAToPtB.z + cylToPtA.z) + cyl->pos.z;
        intFlags |= 4;
    }

    /**
     * Places the found intersection points into intersectA and intersectB. IntersectA is always closer to point A
     */
    for (count = 0, i = 0; i < 4; i++) {
        if (intFlags & (1 << i)) {
            if (count == 0) {
                *intersectA = intPts[i];
            } else if (count == 1) {
                if (Math3D_Vec3fDistSq(intersectA, linePointA) < Math3D_Vec3fDistSq(intersectA, &intPts[i])) {
                    *intersectB = intPts[i];
                } else {
                    *intersectB = *intersectA;
                    *intersectA = intPts[i];
                }
                break;
            }
            count++;
        }
    }
    return count;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_8017E350.s")
#endif

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_CylTriVsIntersect(Cylinder16* cyl, TriNorm* tri, Vec3f* intersect) {
    static Sphere16 topSphere;
    static Sphere16 bottomSphere;
    static Vec3f cylIntersectA;
    static Vec3f cylIntersectB;

    f32 yIntersect;
    f32 cylTop;
    f32 cylBottom;
    f32 minDistSq;
    f32 radiusTodistFromCylYIntersectTov0v1;
    f32 distFromPointAToIntersectASq;
    Vec3f cylIntersectCenter;

    cylBottom = (f32)cyl->pos.y + cyl->yShift;
    cylTop = cyl->height + cylBottom;

    if (((tri->vtx[0].y < cylBottom) && (tri->vtx[1].y < cylBottom) && (tri->vtx[2].y < cylBottom)) ||
        ((cylTop < tri->vtx[0].y) && (cylTop < tri->vtx[1].y) && (cylTop < tri->vtx[2].y))) {
        // If all of the verticies are below or all of the verticies are above the cylinder.
        return false;
    }

    minDistSq = 1.e38f;
    if (Math3D_CylVsLineSeg(cyl, &tri->vtx[0], &tri->vtx[1], &cylIntersectA, &cylIntersectB)) {
        distFromPointAToIntersectASq = Math3D_Vec3fDistSq(&cylIntersectA, &tri->vtx[0]);
        minDistSq = distFromPointAToIntersectASq;
        *intersect = cylIntersectA;
    }

    if (Math3D_CylVsLineSeg(cyl, &tri->vtx[2], &tri->vtx[1], &cylIntersectA, &cylIntersectB)) {
        distFromPointAToIntersectASq = Math3D_Vec3fDistSq(&cylIntersectA, &tri->vtx[2]);
        if (distFromPointAToIntersectASq < minDistSq) {
            *intersect = cylIntersectA;
            minDistSq = distFromPointAToIntersectASq;
        }
    }

    if (Math3D_CylVsLineSeg(cyl, &tri->vtx[0], &tri->vtx[2], &cylIntersectA, &cylIntersectB)) {
        distFromPointAToIntersectASq = Math3D_Vec3fDistSq(&cylIntersectA, &tri->vtx[0]);
        if (distFromPointAToIntersectASq < minDistSq) {
            *intersect = cylIntersectA;
            minDistSq = distFromPointAToIntersectASq;
        }
    }

    if (minDistSq != 1.e38f) {
        return true;
    }

    if (Math3D_TriChkLineSegParaYIntersect(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], tri->plane.normal.x,
                                           tri->plane.normal.y, tri->plane.normal.z, tri->plane.originDist, cyl->pos.z,
                                           cyl->pos.x, &yIntersect, cylBottom, cylTop)) {
        Vec3f midpointv0v1;
        Vec3f diffMidpointIntersect;
        f32 distFromCylYIntersectTov0v1;
        s32 pad;

        cylIntersectCenter.x = cyl->pos.x;
        cylIntersectCenter.y = yIntersect;
        cylIntersectCenter.z = cyl->pos.z;

        midpointv0v1.x = (tri->vtx[0].x + tri->vtx[1].x) * 0.5f;
        midpointv0v1.y = (tri->vtx[0].y + tri->vtx[1].y) * 0.5f;
        midpointv0v1.z = (tri->vtx[0].z + tri->vtx[1].z) * 0.5f;

        Math_Vec3f_Diff(&midpointv0v1, &cylIntersectCenter, &diffMidpointIntersect);
        distFromCylYIntersectTov0v1 = sqrtf(SQ(diffMidpointIntersect.x) + SQ(diffMidpointIntersect.z));

        if (IS_ZERO(distFromCylYIntersectTov0v1)) {
            Math_Vec3f_Copy(intersect, &midpointv0v1);
            return true;
        }

        radiusTodistFromCylYIntersectTov0v1 = cyl->radius / distFromCylYIntersectTov0v1;
        Math3D_PointOnInfiniteLine(&cylIntersectCenter, &diffMidpointIntersect, radiusTodistFromCylYIntersectTov0v1,
                                   intersect);
        return true;
    }

    topSphere.center.x = bottomSphere.center.x = cyl->pos.x;
    topSphere.center.z = bottomSphere.center.z = cyl->pos.z;
    topSphere.center.y = cylTop;
    bottomSphere.center.y = cylBottom;
    topSphere.radius = bottomSphere.radius = cyl->radius;

    if ((Math3D_TriVsSphIntersect(&topSphere, tri, intersect)) ||
        (Math3D_TriVsSphIntersect(&bottomSphere, tri, intersect))) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_ColCylinderTri.s")
#endif

s32 Math3D_CylVsTri(Cylinder16* cyl, TriNorm* tri) {
    Vec3f intersect;

    return Math3D_CylTriVsIntersect(cyl, tri, &intersect);
}

s32 Math3D_SphVsSph(Sphere16* sphereA, Sphere16* sphereB) {
    f32 overlapSize;

    return Math3D_SphVsSphOverlap(sphereA, sphereB, &overlapSize);
}

s32 Math3D_SphVsSphOverlap(Sphere16* sphereA, Sphere16* sphereB, f32* overlapSize) {
    f32 centerDist;

    return Math3D_SphVsSphOverlapCenter(sphereA, sphereB, overlapSize, &centerDist);
}

s32 Math3D_SphVsSphOverlapCenter(Sphere16* sphereA, Sphere16* sphereB, f32* overlapSize, f32* centerDist) {
    Vec3f diff;

    diff.x = (f32)sphereA->center.x - (f32)sphereB->center.x;
    diff.y = (f32)sphereA->center.y - (f32)sphereB->center.y;
    diff.z = (f32)sphereA->center.z - (f32)sphereB->center.z;

    *centerDist = sqrtf(SQ(diff.x) + SQ(diff.y) + SQ(diff.z));

    *overlapSize = (((f32)sphereA->radius + (f32)sphereB->radius) - *centerDist);
    if (*overlapSize > 0.008f) {
        return true;
    }

    *overlapSize = 0.0f;
    return false;
}

s32 Math3D_SphVsCylOverlapDist(Sphere16* sph, Cylinder16* cyl, f32* overlapSize) {
    f32 centerDist;

    return Math3D_SphVsCylOverlapCenterDist(sph, cyl, overlapSize, &centerDist);
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_SphVsCylOverlapCenterDist(Sphere16* sph, Cylinder16* cyl, f32* overlapSize, f32* centerDist) {
    static Cylinderf cylf;
    static Spheref sphf;

    f32 x;
    f32 z;
    f32 combinedRadius;
    f32 cylBottom;
    f32 cylTop;
    f32 sphBottom;
    f32 sphTop;

    if (sph->radius <= 0 || cyl->radius <= 0) {
        // either radius is 0
        return false;
    }
    sphf.center.y = sph->center.y;
    sphf.radius = sph->radius;
    cylf.pos.y = cyl->pos.y;
    cylf.yShift = cyl->yShift;
    cylf.height = cyl->height;
    x = (f32)sph->center.x - cyl->pos.x;
    z = (f32)sph->center.z - cyl->pos.z;
    combinedRadius = (f32)sph->radius + cyl->radius;
    *centerDist = sqrtf(SQ(x) + SQ(z));
    if (combinedRadius < *centerDist) {
        // if the combined radii is less than the distance to the centers, they cannot be touching.
        return false;
    }

    cylBottom = (cylf.pos.y + cylf.yShift);
    cylTop = cylBottom + cylf.height;
    sphBottom = sphf.center.y - sphf.radius;
    sphTop = sphf.center.y + sphf.radius;

    if ((sphTop >= cylBottom) && (sphBottom <= cylTop)) {
        // if the cylinder and sphere are intersecting on the xz plane, check if they're intersecting on
        // the y axis.
        *overlapSize = combinedRadius - *centerDist;
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_ColSphereCylinderDistanceAndAmount.s")
#endif

s32 Math3D_CylOutsideCyl(Cylinder16* ca, Cylinder16* cb, f32* deadSpace) {
    f32 xzDist;

    return Math3D_CylOutsideCylDist(ca, cb, deadSpace, &xzDist);
}

#ifdef NON_MATCHING
// in-function static bss
s32 Math3D_CylOutsideCylDist(Cylinder16* ca, Cylinder16* cb, f32* deadSpace, f32* xzDist) {
    static Cylinderf caf;
    static Cylinderf cbf;

    Math_Vec3s_ToVec3f(&caf.pos, &ca->pos);
    caf.radius = ca->radius;
    caf.yShift = ca->yShift;
    caf.height = ca->height;

    Math_Vec3s_ToVec3f(&cbf.pos, &cb->pos);
    cbf.radius = cb->radius;
    cbf.yShift = cb->yShift;
    cbf.height = cb->height;

    *xzDist = sqrtf(SQ(caf.pos.x - cbf.pos.x) + SQ(caf.pos.z - cbf.pos.z));

    // The combined radix are within the xz distance
    if ((caf.radius + cbf.radius) < *xzDist) {
        return false;
    }

    // top of ca < bottom of cb or top of cb < bottom of ca
    if (((caf.pos.y + caf.yShift) + caf.height) < (cbf.pos.y + cbf.yShift) ||
        (((cbf.pos.y + cbf.yShift) + cbf.height) < (caf.pos.y + caf.yShift))) {
        return false;
    }

    *deadSpace = caf.radius + cbf.radius - *xzDist;
    return true;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/Math3D_ColCylinderCylinderAmountAndDistance.s")
#endif

#define Math3D_TriVsTriIntersect Math3d_ColTriTri
s32 Math3D_TriVsTriIntersect(TriNorm* ta, TriNorm* tb, Vec3f* intersect) {
    f32 dist0 = Math3D_Plane(&ta->plane, &tb->vtx[0]);
    f32 dist1 = Math3D_Plane(&ta->plane, &tb->vtx[1]);
    f32 dist2 = Math3D_Plane(&ta->plane, &tb->vtx[2]);

    if (((dist0 > 0.0f) && (dist1 > 0.0f) && (dist2 > 0.0f)) ||
        (((dist0 < 0.0f) && (dist1 < 0.0f)) && (dist2 < 0.0f))) {
        return false;
    }

    dist0 = Math3D_Plane(&tb->plane, &ta->vtx[0]);
    dist1 = Math3D_Plane(&tb->plane, &ta->vtx[1]);
    dist2 = Math3D_Plane(&tb->plane, &ta->vtx[2]);

    if ((((dist0 > 0.0f) && (dist1 > 0.0f)) && (dist2 > 0.0f)) ||
        ((dist0 < 0.0f) && (dist1 < 0.0f) && (dist2 < 0.0f))) {
        return false;
    }

    if (Math3D_TriLineIntersect(&tb->vtx[0], &tb->vtx[1], &tb->vtx[2], tb->plane.normal.x, tb->plane.normal.y,
                                tb->plane.normal.z, tb->plane.originDist, &ta->vtx[0], &ta->vtx[1], intersect, 0)) {
        return true;
    }
    if (Math3D_TriLineIntersect(&tb->vtx[0], &tb->vtx[1], &tb->vtx[2], tb->plane.normal.x, tb->plane.normal.y,
                                tb->plane.normal.z, tb->plane.originDist, &ta->vtx[1], &ta->vtx[2], intersect, 0)) {
        return true;
    }
    if (Math3D_TriLineIntersect(&tb->vtx[0], &tb->vtx[1], &tb->vtx[2], tb->plane.normal.x, tb->plane.normal.y,
                                tb->plane.normal.z, tb->plane.originDist, &ta->vtx[2], &ta->vtx[0], intersect, 0)) {
        return true;
    }
    if (Math3D_TriLineIntersect(&ta->vtx[0], &ta->vtx[1], &ta->vtx[2], ta->plane.normal.x, ta->plane.normal.y,
                                ta->plane.normal.z, ta->plane.originDist, &tb->vtx[0], &tb->vtx[1], intersect, 0)) {
        return true;
    }
    if (Math3D_TriLineIntersect(&ta->vtx[0], &ta->vtx[1], &ta->vtx[2], ta->plane.normal.x, ta->plane.normal.y,
                                ta->plane.normal.z, ta->plane.originDist, &tb->vtx[1], &tb->vtx[2], intersect, 0)) {
        return true;
    }
    if (Math3D_TriLineIntersect(&ta->vtx[0], &ta->vtx[1], &ta->vtx[2], ta->plane.normal.x, ta->plane.normal.y,
                                ta->plane.normal.z, ta->plane.originDist, &tb->vtx[2], &tb->vtx[0], intersect, 0)) {
        return true;
    }
    return false;
}


s32 Math3D_XZInSphere(Sphere16* sphere, f32 x, f32 z) {
    f32 xDiff = sphere->center.x - x;
    f32 zDiff = sphere->center.z - z;

    if ((SQ(xDiff) + SQ(zDiff)) <= SQ(sphere->radius)) {
        return true;
    }
    return false;
}

s32 Math3D_XYInSphere(Sphere16* sphere, f32 x, f32 y) {
    f32 xDiff = sphere->center.x - x;
    f32 yDiff = sphere->center.y - y;

    if ((SQ(xDiff) + SQ(yDiff)) <= SQ(sphere->radius)) {
        return true;
    }
    return false;
}

s32 Math3D_YZInSphere(Sphere16* sphere, f32 y, f32 z) {
    f32 yDiff = sphere->center.y - y;
    f32 zDiff = sphere->center.z - z;

    if ((SQ(yDiff) + SQ(zDiff)) <= SQ(sphere->radius)) {
        return true;
    }
    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_math3d/func_8017FB1C.s")

void func_8017FD44(Vec3f* arg0, Vec3f* arg1, Vec3f* dst, f32 arg3) {
    Vec3f sp2C;
    s16 sp2A;
    f32 sp24;

    if (!(arg3 < -1.0f) || !(arg3 > 1.0f)) {
        sp2C.x = (arg0->x + arg1->x) * 0.5f;
        sp2C.z = (arg0->z + arg1->z) * 0.5f;
        sp24 = sqrtf(SQ(sp2C.x - arg0->x) + SQ(sp2C.z - arg0->z));
        dst->y = (arg1->y - arg0->y) * arg3 + arg0->y;
        sp2A = Math_Vec3f_Yaw(&sp2C, arg0);
        dst->x = Math_SinS((s16)(32767.0f * arg3) + sp2A) * sp24 + sp2C.x;
        dst->z = Math_CosS((s16)(32767.0f * arg3) + sp2A) * sp24 + sp2C.z;
    }
}
