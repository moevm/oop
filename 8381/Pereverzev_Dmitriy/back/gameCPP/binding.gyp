{
    "targets": [
        {
            "target_name": "my_game_cpp",
            "cflags": [
                "-std=c++17",

            ],
            "conditions": [
                [
                    "OS=='mac'",
                    {
                        "xcode_settings": {
                            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                            "OTHER_CPLUSPLUSFLAGS": [
                                "-mmacosx-version-min=10.15",
                                "-w"
                                
                            ],
                            "OTHER_LDFLAGS": [
                                "-stdlib=libc++"
                            ],
                        },
                    }
                ],
            ],
            'xcode_settings': {
                'OTHER_CFLAGS': [
                    "-std=c++17",
                    "-stdlib=libc++",
                    "-mmacosx-version-min=10.15"
                ],
            },
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            "sources": [
                "<!@(node ./fileFinder.js .cpp .cc)"
               
            ],
        }
    ]
}