#ifndef CADMIUM_EXAMPLE_CELLDEVS_Pedestrian_CELL_HPP_
#define CADMIUM_EXAMPLE_CELLDEVS_Pedestrian_CELL_HPP_

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/celldevs/grid/cell.hpp>
#include <cadmium/celldevs/grid/config.hpp>
#include "state.hpp"

namespace cadmium::celldevs::example::pedestrianEvacuation {
	//! Synthetic pedestrianEvacuation cell.
	class GridPedestrianCell : public GridCell<PedestrianCell, double> {
		double cellstate;
		double exit_locations;
		double x;
		double y;
			
	 public:
		GridPedestrianCell(const std::vector<int>& id, const std::shared_ptr<const GridCellConfig<PedestrianCell, double>>& config):
		  GridCell<PedestrianCell, double>(id, config), cellstate() , exit_locations() ,x(),y() {}

		[[nodiscard]] PedestrianCell localComputation(PedestrianCell state,
		  const std::unordered_map<std::vector<int>, NeighborData<PedestrianCell, double>>& neighborhood) const override {
	 switch (state.cellstate) {
                case 1: // pedestrian moving upwards
                    state.y -= 1;
                    break;
                case 2: // pedestrian moving downwards
                    state.y += 1;
                    break;
                case 3: // pedestrian moving left with reference to wall
                    state.x -= 1;
                    state.y -= 1;
                    break;
                case 4: // pedestrian moving right with reference to wall
                    state.x += 1;
                    state.y += 1;
                    break;
                default:
                    break;
            }

   // Check if pedestrian has found an exit
           for (const auto& exit_loc : state.exit_locations) {
    int exit_x = exit_loc[0]["x"].get<int>();
    int exit_y = exit_loc[0]["y"].get<int>();
    if (state.x == exit_x && state.y == exit_y) {
        state.reached_exit=1;
        state.cellstate=0;
		return state;
    }
}
			return state;
		}

		[[nodiscard]] double outputDelay(const PedestrianCell& cellstate) const override {
			return 1.;
		}
	};
}  //namespace admium::celldevs::example::pedestrianEvacuation

#endif //CADMIUM_EXAMPLE_CELLDEVS_Pedestrian_CELL_HPP_
