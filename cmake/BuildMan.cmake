# Fichiers de man
# Compression of the manuals

# Create the man dir
SET(MANUAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/man)
FILE(MAKE_DIRECTORY ${MANUAL_OUTPUT_PATH})

FOREACH(man ${MAN_PAGES})
	GET_FILENAME_COMPONENT(man_name ${man} NAME)
  ADD_CUSTOM_COMMAND(
    OUTPUT ${MANUAL_OUTPUT_PATH}/${man_name}.gz
    COMMAND ${GZIP_TOOL} -c ${PROJECT_SOURCE_DIR}/${man} > ${MANUAL_OUTPUT_PATH}/${man_name}.gz
    DEPENDS ${PROJECT_SOURCE_DIR}/${man}
    COMMENT "Building manpage ${man_name}.gz")
   	LIST(APPEND MAN_GZ_LIST ${MANUAL_OUTPUT_PATH}/${man_name}.gz)
ENDFOREACH()

ADD_CUSTOM_TARGET(man ALL DEPENDS ${MAN_GZ_LIST})

# Install targets !
FOREACH(man ${MAN_GZ_LIST})
	IF(${man} MATCHES "^.*[.]1[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man1")
	ENDIF()
	IF(${man} MATCHES "^.*[.]2[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man2")
	ENDIF()
	IF(${man} MATCHES "^.*[.]3[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man3")
	ENDIF()
	IF(${man} MATCHES "^.*[.]4[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man4")
	ENDIF()
	IF(${man} MATCHES "^.*[.]5[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man5")
	ENDIF()
	IF(${man} MATCHES "^.*[.]6[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man6")
	ENDIF()
	IF(${man} MATCHES "^.*[.]7[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man7")
	ENDIF()
	IF(${man} MATCHES "^.*[.]8[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man8")
	ENDIF()
	IF(${man} MATCHES "^.*[.]9[.]gz$")
		INSTALL(FILES ${man}
				         DESTINATION
				         "man/man9")
	ENDIF()
ENDFOREACH()
