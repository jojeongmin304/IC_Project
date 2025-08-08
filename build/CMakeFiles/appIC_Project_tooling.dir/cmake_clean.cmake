file(REMOVE_RECURSE
  "IC_Project/Gear.qml"
  "IC_Project/InstrumentCluster.qml"
  "IC_Project/LeftCluster.qml"
  "IC_Project/Main.qml"
  "IC_Project/RightCluster.qml"
  "IC_Project/image.qrc"
  "IC_Project/qml.qrc"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appIC_Project_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
