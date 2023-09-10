
/// @brief - A terrain generator.

/// Useful links:
/// https://medium.com/@henchman/adventures-in-procedural-terrain-generation-part-1-b64c29e2367a
/// https://rtouti.github.io/graphics/perlin-noise-algorithm

#include "App.hh"
#include "AppDesc.hh"
#include "IsometricViewFrame.hh"
#include "TopViewFrame.hh"
#include <core_utils/CoreException.hh>
#include <core_utils/LoggerLocator.hh>
#include <core_utils/PrefixedLogger.hh>
#include <core_utils/StdLogger.hh>

#include "IPoint.hh"

int main(int /*argc*/, char ** /*argv*/)
{
  // Create the logger.
  utils::StdLogger raw;
  raw.setLevel(utils::Level::Debug);
  utils::PrefixedLogger logger("pge", "main");
  utils::LoggerLocator::provide(&raw);

  try
  {
    logger.logMessage(utils::Level::Notice, "Starting application");

    auto tiles  = pge::CenteredViewport({5.0f, 4.0f}, {16.0f, 12.0f});
    auto pixels = pge::TopLeftViewport({0.0f, 0.0f}, {800.0f, 600.0f});

    auto frame = std::make_shared<pge::TopViewFrame>(tiles, pixels);

    pge::AppDesc ad = pge::newDesc(olc::vi2d(800, 600), frame, "terrain");
    pge::App demo(ad);

    demo.Start();
  }
  catch (const utils::CoreException &e)
  {
    logger.logError(utils::Level::Critical,
                    "Caught internal exception while setting up application",
                    e.what());
  }
  catch (const std::exception &e)
  {
    logger.logError(utils::Level::Critical,
                    "Caught internal exception while setting up application",
                    e.what());
  }
  catch (...)
  {
    logger.logMessage(utils::Level::Critical, "Unexpected error while setting up application");
  }

  return EXIT_SUCCESS;
}
