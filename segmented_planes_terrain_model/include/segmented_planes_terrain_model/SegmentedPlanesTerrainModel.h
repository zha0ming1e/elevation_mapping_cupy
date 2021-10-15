//
// Created by rgrandia on 23.06.20.
//

#pragma once

#include <convex_plane_decomposition/PlanarRegion.h>
#include <ocs2_switched_model_interface/terrain/TerrainModel.h>

#include <signed_distance_field/GridmapSignedDistanceField.h>

namespace switched_model {

class SegmentedPlanesTerrainModel : public switched_model::TerrainModel {
 public:
  SegmentedPlanesTerrainModel(convex_plane_decomposition::PlanarTerrain planarTerrain);

  TerrainPlane getLocalTerrainAtPositionInWorldAlongGravity(const vector3_t& positionInWorld) const override;

  ConvexTerrain getConvexTerrainAtPositionInWorld(const vector3_t& positionInWorld) const override;

  void createSignedDistanceBetween(const Eigen::Vector3d& minCoordinates, const Eigen::Vector3d& maxCoordinates);

  const signed_distance_field::GridmapSignedDistanceField* getSignedDistanceField() const override { return signedDistanceField_.get(); }

  vector3_t getHighestObstacleAlongLine(const vector3_t& position1InWorld, const vector3_t& position2InWorld) const override;

  std::vector<vector2_t> getHeightProfileAlongLine(const vector3_t& position1InWorld, const vector3_t& position2InWorld) const override;

  const convex_plane_decomposition::PlanarTerrain& planarTerrain() const { return planarTerrain_; }

 private:
  const convex_plane_decomposition::PlanarTerrain planarTerrain_;
  std::unique_ptr<signed_distance_field::GridmapSignedDistanceField> signedDistanceField_;
  const grid_map::Matrix* const elevationData_;
};

std::pair<const convex_plane_decomposition::PlanarRegion*, convex_plane_decomposition::CgalPoint2d> getPlanarRegionAtPositionInWorld(
    const vector3_t& positionInWorld, const std::vector<convex_plane_decomposition::PlanarRegion>& planarRegions);

}  // namespace switched_model
