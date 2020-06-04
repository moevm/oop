using System;
using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using JsonSchemas.Components;
using JsonSchemas.Game;
using JsonSchemas.Generators;
using MonoBehaviours;
using MonoBehaviours.Session;
using WebSocketSharp;
using CaxapCommon.Enums;
// ReSharper disable InconsistentNaming
// ReSharper disable FieldCanBeMadeReadOnly.Global
// ReSharper disable MemberCanBePrivate.Global
// ReSharper disable NotAccessedField.Global
// ReSharper disable IdentifierTypo
// ReSharper disable MemberCanBeProtected.Global


namespace JsonSchemas
{
    public class in_connect : j_typed
    {
        public int version;
        public string nickname;

        public in_connect()
        {
            version = Constants.Version;
            nickname = PlayerPrefsWrapper.Get(StrPrefs.input_nickname);
        }

        public override bool IsValid()
        {
            return base.IsValid() && nickname != "";
        }
    }
    
    public class in_signal : j_typed
    {
        public int version;
        public int sender;

        public in_signal()
        {
            version = Constants.Version;
            sender = PlayerPrefsWrapper.Get(IntPrefs.sender);
        }
        
        public override bool IsValid()
        {
            if (GetType() == typeof(in_signal)) throw new NotImplementedException(GetType() + "shouldn't called");
            return base.IsValid() && sender != 0;
        }
    }


    public class in_server_info : in_signal
    {
        // Nothing
    }


    public class in_read_chat : in_signal
    {
        // Nothing
    }


    public class in_write_chat : in_signal
    {
        public string message;

        public in_write_chat()
        {
            message = PlayerPrefsWrapper.Take(StrPrefs.input_message);
        }

        public override bool IsValid()
        {
            return base.IsValid() && message != "";
        }
    }


    public class in_create_session : in_signal
    {
        public string session_name;

        public in_create_session()
        {
            session_name = PlayerPrefsWrapper.Take(StrPrefs.input_session_name);
        }

        public override bool IsValid()
        {
            return base.IsValid() && session_name != "";
        }
    }


    public class in_signal_session : in_signal
    {
        public int session_id;

        public in_signal_session()
        {
            session_id = PlayerPrefsWrapper.Get(IntPrefs.session_id);
        }

        public override bool IsValid()
        {
            if (GetType() == typeof(in_signal)) throw new NotImplementedException(GetType() + "shouldn't called");
            return base.IsValid() && session_id != 0;
        }
    }
    
    public class in_session_info : in_signal_session 
    {
        // Nothing
    }



    public class in_game_info : in_signal_session
    {
        // Nothing
    }


    public class in_game_load : in_signal_session
    {
        public abstract_game game;

        public in_game_load()
        {
            string data = PlayerPrefsWrapper.Get(StrPrefs.data_save);
            if (!data.IsNullOrEmpty()) game = (abstract_game)JsonManager.Deserialize(data);
        }

        public override bool IsValid()
        {
            return base.IsValid() && game != null;
        }
    }


    public class in_game_save : in_signal_session
    {
        // Nothing
    }


    public class in_game_join : in_signal_session
    {
        // Nothing
    }


    public class in_game_quit : in_signal_session
    {
        // Nothing
    }


    public class in_game_play : in_signal_session
    {
        // Nothing
    }


    public class in_game_pause : in_signal_session
    {
        // Nothing
    }


    public class in_game_stop : in_signal_session
    {
        // Nothing
    }


    public class in_game_setup : in_signal_session
    {
        public abstract_generator generator; // : abstract_generator

        public in_game_setup(GeneratorType generatorType = GeneratorType.simple)
        {
            int seed = PlayerPrefsWrapper.Get(IntPrefs.setup_seed);
            List<int> playersUid = SessionBehaviour.GetPlayers();
            int tilemapScaleX = PlayerPrefsWrapper.Get(IntPrefs.setup_tilemap_scale_x);
            int tilemapScaleY = PlayerPrefsWrapper.Get(IntPrefs.setup_tilemap_scale_y);
            
            switch (generatorType)
            {
                case GeneratorType.simple:
                    generator = new simple(seed, playersUid, tilemapScaleX, tilemapScaleY);
                    break;
                case GeneratorType.perlin:
                    int octaves = PlayerPrefsWrapper.Get(IntPrefs.setup_octaves);
                    float persistance = PlayerPrefsWrapper.Get(IntPrefs.setup_persistance) / 100f;
                    generator = new perlin(seed, octaves, persistance, playersUid, tilemapScaleX, tilemapScaleY);
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(generatorType), generatorType, null);
            }
        }

        public override bool IsValid()
        {
            return base.IsValid() && generator != null && generator.IsValid();
        }
    }


    public class in_game_signal : in_signal_session
    {
        public List<int> units; // : list<int>
        public string component; // : string
        public command data; // : j_{command_name}

        public in_game_signal(List<int> units, string component, command data)
        {
            this.units = units;
            this.component = component;
            this.data = data;
        }

        public override bool IsValid()
        {
            return base.IsValid() && units != null && units.Count > 0 && component != "" && data != null;
        }
    }
}