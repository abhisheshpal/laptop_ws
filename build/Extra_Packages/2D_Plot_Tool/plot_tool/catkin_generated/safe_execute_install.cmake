execute_process(COMMAND "/home/vigneshnuc/laptop_ws/build/Extra_Packages/2D_Plot_Tool/plot_tool/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/vigneshnuc/laptop_ws/build/Extra_Packages/2D_Plot_Tool/plot_tool/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
