cmake_policy(SET CMP0057 NEW)

# error on home not set
if(NOT NCREPORT_HOME)
  set(NCREPORT_HOME $ENV{NCREPORT_HOME})
endif()

if("${NCREPORT_HOME}" STREQUAL "")
  # TODO: use submodule instead
  message("-- NCREPORT_HOME not set, using NCReport submodule instead")
  set(NCREPORT_HOME ${CMAKE_CURRENT_LIST_DIR}/../ncreport)
endif()

if(NOT TARGET NCReport)

project(NCReport)

option(WITH_PREVIEWWINDOW "Enable PREVIEWWINDOW support" OFF)
option(WITH_PRINT_DIALOG "Enable Print dialog support" OFF)
option(WITH_DESKTOP "Enable Desktop support" OFF)
option(WITH_SVG "Enable SVG support" ON)
option(WITH_PRINT "Enable Print support" ON)
option(WITH_SQL "Enable SQL support" ON)
option(WITH_EMAIL "Enable EMAIL support" ON)
option(WITH_TABLEVIEW "Enable TABLEVIEW support" ON)
option(WITH_HIGHCHARTS "Enable HIGHCHARTS support" ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(NCREPORT_SRC_DIR ${NCREPORT_HOME}/src/ncreport)

find_package(Qt5 COMPONENTS Xml Gui Widgets Sql Script Core Network REQUIRED)

set(SOURCES
  ${NCREPORT_SRC_DIR}/ncreportscale.cpp
  ${NCREPORT_SRC_DIR}/ncreportdef.cpp
  ${NCREPORT_SRC_DIR}/ncreportxmlreader.cpp
  ${NCREPORT_SRC_DIR}/ncreportoutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportdata.cpp
  ${NCREPORT_SRC_DIR}/ncreportsection.cpp
  ${NCREPORT_SRC_DIR}/ncreportgroup.cpp
  ${NCREPORT_SRC_DIR}/ncreportparameter.cpp
  ${NCREPORT_SRC_DIR}/ncreportvariable.cpp
  ${NCREPORT_SRC_DIR}/ncreportpageoption.cpp
  ${NCREPORT_SRC_DIR}/ncreportdatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreportfielditem.cpp
  ${NCREPORT_SRC_DIR}/ncreportitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportlabelitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportlineitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportrectitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportimageitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportbarcodeitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportshapeitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportevaluator.cpp
  ${NCREPORT_SRC_DIR}/ncreportdirector.cpp
  ${NCREPORT_SRC_DIR}/ncreport.cpp
  ${NCREPORT_SRC_DIR}/ncreportsource.cpp
  ${NCREPORT_SRC_DIR}/ncreportxmldefreader.cpp
  ${NCREPORT_SRC_DIR}/ncreporttextdatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreporttxtdatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreportxmlwriter.cpp
  ${NCREPORT_SRC_DIR}/ncreportxmldefwriter.cpp
  ${NCREPORT_SRC_DIR}/ncreportstringlistdatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreportgraphitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportgraphrenderer.cpp
  ${NCREPORT_SRC_DIR}/ncreportabstractitemrendering.cpp
  ${NCREPORT_SRC_DIR}/ncreportitemmodeldatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreporttextitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportsectiondirector.cpp
  ${NCREPORT_SRC_DIR}/ncreportutils.cpp
  ${NCREPORT_SRC_DIR}/ncreportbarcoderenderer.cpp
  ${NCREPORT_SRC_DIR}/ncreporthttpclient.cpp
  ${NCREPORT_SRC_DIR}/ncreportmarkuplanguageoutput.cpp
  ${NCREPORT_SRC_DIR}/ncreporthtmloutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportdatasourcefactory.cpp
  ${NCREPORT_SRC_DIR}/ncreportdummydatasourcefactory.cpp
  ${NCREPORT_SRC_DIR}/ncreportdatafieldinfo.cpp
  ${NCREPORT_SRC_DIR}/ncreportcustomdsprovider.cpp
  ${NCREPORT_SRC_DIR}/ncreportcrosstabitemcell.cpp
  ${NCREPORT_SRC_DIR}/ncreportcrosstabitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportellipseitem.cpp
  ${NCREPORT_SRC_DIR}/ncreportconditionalformat.cpp
  ${NCREPORT_SRC_DIR}/ncreportpivottablemodel.cpp
  ${NCREPORT_SRC_DIR}/ncreportimageoutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportwidgetrenderer.cpp
  ${NCREPORT_SRC_DIR}/ncreporttextoutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportprinteroutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportpdfoutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportpdfwriteroutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportxmldatasource.cpp
  ${NCREPORT_SRC_DIR}/ncreportuserfunction.cpp
  ${NCREPORT_SRC_DIR}/ncreportexcelhtmloutput.cpp
  ${NCREPORT_SRC_DIR}/ncreportvariablemodifier.cpp
  ${NCREPORT_SRC_DIR}/ncreportprinter.cpp
  ${NCREPORT_SRC_DIR}/ncreportdatasourcerelation.cpp
  ${NCREPORT_SRC_DIR}/ncreportdataformat.cpp
  ${NCREPORT_SRC_DIR}/ncreportsourcefactory.cpp
  ${NCREPORT_SRC_DIR}/ncreportfactory.cpp
  ${NCREPORT_SRC_DIR}/NCReportGraphicsViewItem.cpp
  ${NCREPORT_SRC_DIR}/NCReportGraphicsViewItem_p.cpp
  ${NCREPORT_SRC_DIR}/ncreporttextstyle.cpp
)

set(DEPENDENCIES
  Qt5::Xml
  Qt5::Core 
  Qt5::Gui
  Qt5::Widgets
  Qt5::Script
  Qt5::Network
)

add_library(NCReport ${SOURCES})
target_include_directories(NCReport PUBLIC ${NCREPORT_SRC_DIR})

if(NOT WITH_DESKTOP)
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_DESKTOP)
endif()

if(WITH_PRINT)
  set(DEPENDENCIES ${DEPENDENCIES} Qt5::PrintSupport)
else()
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_QPRINTER)
endif()

if(NOT WITH_PRINT_DIALOG)
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_PRINT_DIALOG)
endif()

if(WITH_SVG)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/ncreportsvgoutput.cpp
  )
  set(DEPENDENCIES ${DEPENDENCIES} Qt5::Svg)
else()
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_SVG)
endif()

if(WITH_SQL)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/ncreportsqldatasource.cpp
  )
  set(DEPENDENCIES ${DEPENDENCIES} Qt5::Sql)
endif()

if(WITH_PREVIEWWINDOW)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/ncreportpreviewoutput.cpp
    ${NCREPORT_SRC_DIR}/ncreportqtpreviewoutput.cpp
    ${NCREPORT_SRC_DIR}/ncreportpreviewwindow.cpp
    ${NCREPORT_SRC_DIR}/ncreportpreviewpagecontainer.cpp
    ${NCREPORT_SRC_DIR}/ncreportpreviewpage.cpp
  )
else()
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_PREVIEW_WINDOW)
endif()

if(WITH_EMAIL)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/email/mailsender.cpp 
    ${NCREPORT_SRC_DIR}/email/mailsender_p.cpp
  )
else()
  target_compile_definitions(NCReport PRIVATE NCREPORT_NO_EMAIL)
endif()

if(WITH_TABLEVIEW)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/ncreporttableitem.cpp
  )
endif()

if(WITH_HIGHCHARTS)
  target_sources(NCReport PRIVATE
    ${NCREPORT_SRC_DIR}/ncreportchartitem.cpp
    ${NCREPORT_SRC_DIR}/ncreporthighchartsmanager.cpp
  )
endif()
message("Deps = ${DEPENDENCIES}" )

target_link_libraries(NCReport PUBLIC ${DEPENDENCIES})

endif()

## use system ncreport if not set
# if(NOT NCREPORT_HOME)
#   if(UNIX AND NOT APPLE)
#     set(NCREPORT_HOME "/usr/local/NCReport")
#   endif()
# endif()

# set(NCReport_INCLUDE_DIRS "${NCREPORT_HOME}/include")
# if(UNIX AND NOT APPLE)
#   set(NCReport_LIBRARIES "${NCREPORT_HOME}/lib/libNCReport.so")
# elseif(WIN32)
#   # TODO: use proper name format for windows
#   set(NCReport_LIBRARIES ${NCREPORT_HOME}/lib/libNCReport.so)
# endif()