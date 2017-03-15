#pragma once

#include <mbgl/programs/circle_program.hpp>
#include <mbgl/programs/fill_program.hpp>
#include <mbgl/programs/line_program.hpp>
#include <mbgl/programs/raster_program.hpp>
#include <mbgl/programs/symbol_program.hpp>
#include <mbgl/programs/debug_program.hpp>
#include <mbgl/programs/collision_box_program.hpp>
#include <mbgl/programs/program_parameters.hpp>

namespace mbgl {

class Programs {
public:
    Programs(gl::Context& context,
             const ProgramParameters& programParameters,
             const std::string& cacheDir)
        : circle(context, programParameters, cacheDir),
          fill(context, programParameters, cacheDir),
          fillPattern(context, programParameters, cacheDir),
          fillOutline(context, programParameters, cacheDir),
          fillOutlinePattern(context, programParameters, cacheDir),
          line(context, programParameters, cacheDir),
          lineSDF(context, programParameters, cacheDir),
          linePattern(context, programParameters, cacheDir),
          raster(context, programParameters, cacheDir),
          symbolIcon(context, programParameters, cacheDir),
          symbolIconSDF(context, programParameters, cacheDir),
          symbolGlyph(context, programParameters, cacheDir),
          debug(context, ProgramParameters(programParameters.pixelRatio, false), cacheDir),
          collisionBox(context, ProgramParameters(programParameters.pixelRatio, false), cacheDir) {
    }

    CircleProgram circle;
    FillProgram fill;
    FillPatternProgram fillPattern;
    FillOutlineProgram fillOutline;
    FillOutlinePatternProgram fillOutlinePattern;
    LineProgram line;
    LineSDFProgram lineSDF;
    LinePatternProgram linePattern;
    RasterProgram raster;
    SymbolIconProgram symbolIcon;
    SymbolSDFIconProgram symbolIconSDF;
    SymbolSDFTextProgram symbolGlyph;

    DebugProgram debug;
    CollisionBoxProgram collisionBox;
};

} // namespace mbgl
