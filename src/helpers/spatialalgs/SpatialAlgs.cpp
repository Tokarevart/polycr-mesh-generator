#include "SpatialAlgs.h"




#define DET(a, b, c, d) \
        ((a) * (d) - (b) * (c))

#define BETWEEN(p0_coor, p1_coor, p) \
        (std::min(p0_coor, p1_coor) - EPS < (p) && (p) < std::max(p0_coor, p1_coor) + EPS)

#define INSIDE_RECTANGLE(corner0, corner1, point) \
        (BETWEEN(corner0.coors[0], corner1.coors[0], point.coors[0]) && \
         BETWEEN(corner0.coors[1], corner1.coors[1], point.coors[1]) && \
         BETWEEN(corner0.coors[2], corner1.coors[2], point.coors[2]))

#define PI         3.141592653589793
#define PI_DIV_180 0.017453292519943295




tva::Point3 tva::spatialalgs::project(
    const tva::Point3& point, 
    const tva::Point3& line_p0, const tva::Point3& line_p1)
{
    return line_p0 + (point - line_p0).project(line_p1 - line_p0);
}


bool tva::spatialalgs::project(
    tva::Point3& out, 
    const tva::Point3& point, 
    const tva::Point3& segm_p0, const tva::Point3& segm_p1)
{
    tva::Vec3 res = segm_p0 + (point - segm_p0).project(segm_p1 - segm_p0);

    const double EPS = (segm_p1 - segm_p0).magnitude() * 1e-6;
    if (INSIDE_RECTANGLE(
            segm_p0,
            segm_p1,
            res))
    {
        out = res;
        return true;
    }

    return false;
}




bool tva::spatialalgs::isRayIntersectPlane(
    const tva::Vec3& dir,
    const tva::Point3& pl_p0, const tva::Point3& pl_p1, const tva::Point3& pl_p2)
{
    tva::Vec3 edges[2]{ pl_p1 - pl_p0, pl_p2 - pl_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    return det > 1e-6 || det < -1e-6;
}


bool tva::spatialalgs::rayIntersectPlane(
    tva::Point3& out_intersectPoint, 
    const tva::Point3& origin, const tva::Vec3& dir, 
    const tva::Point3& pl_p0, const tva::Point3& pl_p1, const tva::Point3& pl_p2)
{
    tva::Vec3 edges[2]{ pl_p1 - pl_p0, pl_p2 - pl_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    if (det < 1e-6 && det > -1e-6)
        return false;

    tva::Vec3 tvec = origin - pl_p0;
    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);

    double t = tva::Vec3::dotProduct(edges[1], qvec) / det;
    out_intersectPoint = origin + t * dir;
    return t > 0.0;
}


bool tva::spatialalgs::isRayIntersectTriangle(
    const tva::Point3& origin, const tva::Vec3& dir, 
    const tva::Point3& tr_p0, const tva::Point3& tr_p1, const tva::Point3& tr_p2)
{
    tva::Vec3 edges[2]{ tr_p1 - tr_p0, tr_p2 - tr_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    if (det < 1e-6 && det > -1e-6)
        return false;

    double inv_det = 1.0 / det;

    tva::Vec3 tvec = origin - tr_p0;
    double u = tva::Vec3::dotProduct(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0)
        return false;

    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);
    double v = tva::Vec3::dotProduct(dir, qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = tva::Vec3::dotProduct(edges[1], qvec) * inv_det;
    return t > 0.0;
}


bool tva::spatialalgs::lineIntersectPlane(
    tva::Point3& out_intersectPoint,
    const tva::Point3& line_point, const tva::Point3& line_dir,
    const tva::Point3& plane_p0, const tva::Point3& plane_p1, const tva::Point3& plane_p2)
{
    tva::Vec3 edges[2]{ plane_p1 - plane_p0, plane_p2 - plane_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(line_dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    if (det < 1e-6 && det > -1e-6)
        return false;

    tva::Vec3 tvec = line_point - plane_p0;
    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);

    double t = tva::Vec3::dotProduct(edges[1], qvec) / det;
    out_intersectPoint = line_point + t * line_dir;
    return true;
}


const tva::Point3 tva::spatialalgs::lineIntersectPlane(
    const tva::Point3& line_point, const tva::Point3& line_dir, 
    const tva::Point3& plane_p0, const tva::Point3& plane_p1, const tva::Point3& plane_p2)
{
    tva::Vec3 edges[2]{ plane_p1 - plane_p0, plane_p2 - plane_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(line_dir, edges[1]);
    tva::Vec3 tvec = line_point - plane_p0;
    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);

    double t = tva::Vec3::dotProduct(edges[1], qvec) / tva::Vec3::dotProduct(edges[0], pvec);
    return line_point + t * line_dir;
}


bool tva::spatialalgs::isSegmentIntersectTriangle(
    const tva::Point3& segm_p0, const tva::Point3& segm_p1,
    const tva::Point3& tr_p0, const tva::Point3& tr_p1, const tva::Point3& tr_p2)
{
    const tva::Vec3 dir = segm_p1 - segm_p0;

    tva::Vec3 edges[2]
    { tr_p1 - tr_p0,
        tr_p2 - tr_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    if (det < 1e-6 && det > -1e-6)
        return false;

    double inv_det = 1.0 / det;

    tva::Vec3 tvec = segm_p0 - tr_p0;
    double u = tva::Vec3::dotProduct(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0)
        return false;

    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);
    double v = tva::Vec3::dotProduct(dir, qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = tva::Vec3::dotProduct(edges[1], qvec) * inv_det;
    return t < 1.0 && t > 0.0;
}


bool tva::spatialalgs::segmentIntersectPlane(
    tva::Point3& out_intersectPoint,
    const tva::Point3& p0, const tva::Point3& p1, 
    const tva::Point3& pl_p0, const tva::Point3& pl_p1, const tva::Point3& pl_p2)
{
    const tva::Vec3 dir = p1 - p0;

    tva::Vec3 edges[2]{ pl_p1 - pl_p0, pl_p2 - pl_p0 };

    tva::Vec3 pvec = tva::Vec3::crossProduct(dir, edges[1]);
    double det = tva::Vec3::dotProduct(edges[0], pvec);
    if (det < 1e-6 && det > -1e-6)
        return false;

    tva::Vec3 tvec = p0 - pl_p0;
    tva::Vec3 qvec = tva::Vec3::crossProduct(tvec, edges[0]);

    double t = tva::Vec3::dotProduct(edges[1], qvec) / det;
    out_intersectPoint = p0 + t * dir;
    return t < 1.0 && t > 0.0;
}




bool tva::spatialalgs::isPointOnTriangle(
    const tva::Point3& point, 
    const tva::Point3& trngl_p0, const tva::Point3& trngl_p1, const tva::Point3& trngl_p2)
{
    double s0 = tva::Vec3::crossProduct(trngl_p0 - point, trngl_p1 - point).magnitude();
    double s1 = tva::Vec3::crossProduct(trngl_p0 - point, trngl_p2 - point).magnitude();
    double s2 = tva::Vec3::crossProduct(trngl_p1 - point, trngl_p2 - point).magnitude();
    double s = tva::Vec3::crossProduct(trngl_p0 - trngl_p2, trngl_p1 - trngl_p2).magnitude();

    return (s - s0 - s1 - s2) > -1e-6 && (s - s0 - s1 - s2) < 1e-6;
}




double tva::spatialalgs::linesDistance(
    const tva::Point3& line0_p0, const tva::Point3& line0_p1, 
    const tva::Point3& line1_p0, const tva::Point3& line1_p1)
{
    tva::Vec3 u = line0_p1 - line0_p0;
    tva::Vec3 v = line1_p1 - line1_p0;
    tva::Vec3 w = line0_p0 - line1_p0;
    double a = tva::Vec3::dotProduct(u, u); // Always >= 0
    double b = tva::Vec3::dotProduct(u, v);
    double c = tva::Vec3::dotProduct(v, v); // Always >= 0
    double d = tva::Vec3::dotProduct(u, w);
    double e = tva::Vec3::dotProduct(v, w);
    double D = DET(a, b, b, c); // Always >= 0
    double sc, tc;

    // Compute the line parameters of the two closest points
    if (D < 1e-6) // The lines are almost parallel
    {
        sc = 0.0;
        tc = (b > c ? d / b : e / c); // Use the largest denominator
    }
    else
    {
        sc = DET(b, c, d, e) / D;
        tc = DET(a, b, d, e) / D;
    }

    // Get the difference of the two closest points
    tva::Vec3 diff_p = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

    return diff_p.magnitude();   // Return the closest distance
}


double tva::spatialalgs::segmentsDistance(
    const tva::Point3& segm0_p0, const tva::Point3& segm0_p1,
    const tva::Point3& segm1_p0, const tva::Point3& segm1_p1)
{
    tva::Vec3 u = segm0_p1 - segm0_p0;
    tva::Vec3 v = segm1_p1 - segm1_p0;
    tva::Vec3 w = segm0_p0 - segm1_p0;
    double a = tva::Vec3::dotProduct(u, u); // Always >= 0
    double b = tva::Vec3::dotProduct(u, v);
    double c = tva::Vec3::dotProduct(v, v); // Always >= 0
    double d = tva::Vec3::dotProduct(u, w);
    double e = tva::Vec3::dotProduct(v, w);
    double D = DET(a, b, b, c); // Always >= 0
    double sc, sN, sD = D; // sc = sN / sD, default sD = D >= 0
    double tc, tN, tD = D; // tc = tN / tD, default tD = D >= 0

                           // Compute the line parameters of the two closest points
    if (D < 1e-6) // The lines are almost parallel
    {
        sN = 0.0; // Force using point P0 on segment S1
        sD = 1.0; // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else // Get the closest points on the infinite lines
    {
        sN = DET(b, c, d, e);
        tN = DET(a, b, d, e);

        if (sN < 0.0) // sc < 0 => the s=0 edge is visible
        {
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) // sc > 1  => the s=1 edge is visible
        {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) // tc < 0 => the t=0 edge is visible
    {
        tN = 0.0;

        // Recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else
        {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) // tc > 1  => the t=1 edge is visible
    {
        tN = tD;

        // Recompute sc for this edge
        if (b - d < 0.0)
            sN = 0;
        else if (b - d > a)
            sN = sD;
        else
        {
            sN = b - d;
            sD = a;
        }
    }

    // Finally do the division to get sc and tc
    sc = (std::abs(sN) < 1e-6 ? 0.0 : sN / sD);
    tc = (std::abs(tN) < 1e-6 ? 0.0 : tN / tD);

    // Get the difference of the two closest points
    tva::Vec3 diff_p = w + (sc * u) - (tc * v); // =  S1(sc) - S2(tc)

    return diff_p.magnitude(); // Return the closest distance
}




double tva::spatialalgs::cpaTime(
    const tva::Point3& start0, const tva::Vec3& vel0, 
    const tva::Point3& start1, const tva::Vec3& vel1)
{
    tva::Vec3 dv = vel0 - vel1;
    double dv2 = tva::Vec3::dotProduct(dv, dv);
    if (dv2 < 1e-6) // The tracks are almost parallel.
        return 0.0;

    tva::Vec3 w0 = start0 - start1;
    return -tva::Vec3::dotProduct(w0, dv) / dv2;
}


double tva::spatialalgs::cpaDistance(
    const tva::Point3& start0, const tva::Vec3& vel0, 
    const tva::Point3& start1, const tva::Vec3& vel1)
{
    double cpa_time = cpaTime(start0, vel0, start1, vel1);
    tva::Vec3 p0 = start0 + (cpa_time * vel0);
    tva::Vec3 p1 = start1 + (cpa_time * vel1);
    return (p1 - p0).magnitude();
}