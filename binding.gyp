{
	"targets": [
		{
				"target_name": "arduino",
				"sources": [ "arduino.cpp" ],
				"include_dirs": [ "/usr/local/include" ],
				"link_settings": {
					"libraries": [ "-lboost_system-mt", "-lboost_thread-mt" ],
					"ldflags": [ "-L/usr/local/lib", "-Wl,-rpath,/usr/local/lib" ]
				}
		},
		{
				"target_name": "imager",
				"sources": [ "imager.cpp" ],
				"include_dirs": [ "/usr/local/include" ],
				"link_settings": {
					"libraries": [ "-lopencv_core", "-lopencv_highgui", "-lopencv_imgproc" ],
					"ldflags": [ "-L/usr/local/lib", "-Wl,-rpath,/usr/local/lib" ]
				}
		}
	]
}
