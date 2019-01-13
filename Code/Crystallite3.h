#pragma once
#include <list>
#include <vector>
#include <memory>
#include "Definitions.h"
#include "Inclusions.h"

using std::vector;
using std::unique_ptr;

class Crystallite3
{
    double _preferredLength;

    template <class T>
    void removePtrsToNullptr(vector<unique_ptr<T>*>& vec);

    enum ExhaustType
    {
        DONT_EXHAUST,
        WITHOUT_NEW_VERTEX,
        WITH_NEW_VERTEX
    };

    #define debug debug
    void debug();

public:
    vector<ShellFacet3*> shellFacets;
    vector<ShellEdge3*> shellEdges;

    vector<unique_ptr<Simplex3>*> innerSimps;
    vector<unique_ptr<Facet3>*> innerFacets;
    vector<unique_ptr<Edge3>*> innerEdges;
    vector<unique_ptr<Vertex3>*> innerVerts;

    vector<unique_ptr<FrontFacet3>*> frontFacets;
    vector<unique_ptr<FrontEdge3>*> frontEdges;

    const bool shellContainsVertex(const Vertex3& vert);
    void setStartFront(const vector<unique_ptr<Edge3>*>& edges, const vector<unique_ptr<Facet3>*>& facets);
    void computeFrontNormals();

    ShellEdge3* findShellEdge(const ShellVertex3* v0, const ShellVertex3* v1) const;

    unique_ptr<FrontFacet3>* findFrontFacet(const unique_ptr<Facet3>* facet);
    unique_ptr<FrontEdge3>* findFrontEdge(const unique_ptr<Vertex3>* v0, const unique_ptr<Vertex3>* v1);
    unique_ptr<FrontEdge3>* findFrontEdge(const unique_ptr<Edge3>* edge);

    void findAdjacentFrontFacets(
        const unique_ptr<FrontEdge3>* frontEdge,
        unique_ptr<FrontFacet3>*& out_frontFacet0, unique_ptr<FrontFacet3>*& out_frontFacet1) const;
    void findOppositeVertexes(
        const unique_ptr<FrontEdge3>* frontEdge,
        unique_ptr<Vertex3>*& out_vert0, unique_ptr<Vertex3>*& out_vert1) const;
    unique_ptr<FrontEdge3>* findOppositeFrontEdge(const unique_ptr<FrontEdge3>* frontEdge) const;

    // Adds new front facet and corresponding facet.
    unique_ptr<FrontFacet3>* addFrontFacet3(unique_ptr<Edge3>* edge0, unique_ptr<Edge3>* edge1, unique_ptr<Edge3>* edge2);
    unique_ptr<FrontEdge3>* addFrontEdge3(unique_ptr<Vertex3>* vert0, unique_ptr<Vertex3>* vert1);
    void addFrontEdge3(unique_ptr<FrontEdge3>* frontEdge);

    const bool vertexInsideFrontCheck(const Vec3& v);
    const bool lineSegmentGlobalIntersectionCheck(const Vec3& v0, const Vec3& v1);
    const bool segmentFrontIntersectionCheck (const Vec3& v0, const Vec3& v1);
    const bool edgeGlobalIntersectionCheck(const unique_ptr<Edge3>* edge);
    const bool edgeIntersectionCheck  (const unique_ptr<FrontEdge3>* frontEdge);
    const bool facetIntersectionCheck (const unique_ptr<Vertex3>* v0, const unique_ptr<Vertex3>* v1, const Vec3& v2);
    const bool facetIntersectionCheck (const unique_ptr<Vertex3>* v0, const unique_ptr<Vertex3>* v1, const unique_ptr<Vertex3>* v2);
    const bool facetsIntersectionCheck(const unique_ptr<FrontEdge3>* frontEdge);
    const bool insideSimplex3Check(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& vert);
    const bool anyVertexInsidePotentialSimplex3Check(const unique_ptr<FrontEdge3>* frontEdge);
    const bool frontSplitCheck    (const unique_ptr<FrontEdge3>* frontEdge);
    const bool parallelFacetsCheck(const unique_ptr<FrontEdge3>* frontEdge) const;
    const bool frontContainsOfOnly1Simplex3OrEmpty() const;

    static const double computeMinEdgesLength(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);
    static const double computeMaxEdgesLength(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);
    static std::pair<double, double> computeMinMaxEdgesLengths(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);
    static std::pair<double, double> computeMinMaxEdgesSqrLengths(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);
    static const double computeSimplex3SimpleQuality(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);
    static const double computeSimplex3SimpleSqrQuality(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);

    unique_ptr<FrontEdge3>* currentFrontEdge(double maxExCos) const;
    const bool exhaustWithoutNewVertexPriorityPredicate(unique_ptr<FrontEdge3>* frontEdge);
    const bool exhaustWithNewVertexPriorityPredicate   (unique_ptr<FrontEdge3>* frontEdge);
    const ExhaustType exhaustTypeQualityPriorityCalculation(
        unique_ptr<FrontEdge3>* frontEdge,
        unique_ptr<FrontFacet3>** out_withNWFrontFacet = nullptr, Vec3** out_withNWNewVertPos = nullptr);

    Vec3 computeNormalInSimplex3(unique_ptr<FrontFacet3>* frontFacet, const Vec3& oppositeVertPos);
    Vec3 computeNormalInSimplex3(unique_ptr<FrontFacet3>* frontFacet, unique_ptr<Edge3>* oneOfTheRemainingEdges);
    
    void exhaustWithoutNewVertexOppositeEdgeExists    (unique_ptr<FrontEdge3>* frontEdge, unique_ptr<FrontEdge3>* oppositeEdge);
    void exhaustWithoutNewVertexOppositeEdgeDontExists(unique_ptr<FrontEdge3>* frontEdge);
    void exhaustWithoutNewVertex(unique_ptr<FrontEdge3>* frontEdge, const bool oppositeEdgeExistence = true, unique_ptr<FrontEdge3>* oppositeEdge = nullptr);
    

    const bool tryComputeNewVertexPositionType3(unique_ptr<FrontFacet3>* frontFacet, Vec3& out_pos);
    const bool tryComputeNewVertexPositionType2(
        const int smallAngleIndex0, const double angleCos0,
        const int smallAngleIndex1, const double angleCos1,
        unique_ptr<FrontFacet3>* frontFacet, Vec3& out_pos);
    const bool tryComputeNewVertexPositionType1(
        const int smallAngleIndex, const double angleCos, 
        unique_ptr<FrontFacet3>* frontFacet, Vec3& out_pos);
    const bool tryComputeNewVertexPositionType0(unique_ptr<FrontFacet3>* frontFacet, Vec3& out_pos);
    const bool tryComputeNewVertexPosition(unique_ptr<FrontFacet3>* frontFacet, Vec3& out_pos);
    
    unique_ptr<FrontFacet3>* chooseFrontFacetForExhaustionWithNewVertex(unique_ptr<FrontEdge3>* frontEdge);
    void exhaustWithNewVertex(unique_ptr<FrontFacet3>* frontFacet, Vec3 vertPos);
    const bool NewVertexPosition_OLD(unique_ptr<FrontEdge3>* frontEdge, Vec3& out_pos);
    void ExhaustWithNewVertex_OLD(unique_ptr<FrontEdge3>* frontEdge, Vec3 vertPos);

    const bool tryExhaustWithoutNewVertex(unique_ptr<FrontEdge3>* frontEdge, const bool oppositeEdgeExistence = true, unique_ptr<FrontEdge3>* oppositeEdge = nullptr);
    const bool tryExhaustWithNewVertex(unique_ptr<FrontEdge3>* frontEdge);

    const bool ProcessVerySmallAngles(Polycrystal3* polycr);
    const bool ProcessSmallAngles(Polycrystal3* polycr);
    const bool ProcessMediumAngles(Polycrystal3* polycr);
    void ProcessLargeAngles(Polycrystal3* polycr);
    void processAngles(Polycrystal3* polycr);
    void processAngles_OLD(Polycrystal3* polycr);
    const bool globalIntersectionCheck();
    void smoothMesh(int iterationsNum);
    void smoothNotFinisedMesh(int iterationsNum);
    void smoothFront(int iterationsNum);
    void smoothAroundFrontVertex(unique_ptr<Vertex3>* frontVert);
    void analyzeMeshQuality(double& out_minQuality, double& out_avQuality);
    void generateMesh(const double preferredLength, Polycrystal3* polycr);

    Crystallite3();
    ~Crystallite3();
};