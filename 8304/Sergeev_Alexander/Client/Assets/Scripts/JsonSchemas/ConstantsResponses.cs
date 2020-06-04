using System;
using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using GuiConcreteComponents;
using GuiConcreteComponents.Lobby;
using GuiConcreteComponents.Session;
using JsonSchemas.Game;
using JsonSchemas.Online;
using JsonSchemas.Structs;
using Singletons;
using UnityEngine;
using WebSocketSharp;

// ReSharper disable InconsistentNaming
// ReSharper disable UnassignedField.Global
// ReSharper disable MemberCanBePrivate.Global
// ReSharper disable UnusedType.Global
// ReSharper disable MemberCanBeProtected.Global
// ReSharper disable ClassNeverInstantiated.Global


namespace JsonSchemas
{
    public class out_broadcast : j_typed
    {
        public int chat_buffer_updates;

        public override void Execute()
        {
            if (PlayerPrefsWrapper.Get(IntPrefs.chat_buffer_updates) != chat_buffer_updates)
            {
                PlayerPrefsWrapper.Set(IntPrefs.chat_buffer_updates, chat_buffer_updates);
                God.NetworkManager.Send(new in_read_chat());
            }
        }
    }

    public class out_signal : j_typed
    {
        public string error;
        public string success;

        public sealed override void Execute()
        {
            if (error != null)
            {
                MessageBox.Error(error);
                return;
            }
            God.DebugManager.PlayShot();
            HandleSignal();
        }

        public virtual void HandleSignal()
        {
            throw new NotImplementedException(GetType() + "Handling");
        }
    }


    public class out_connect : out_signal // js part
    {
        public List<string> users;

        public override void HandleSignal()
        {
            God.NetworkManager.Users = users;
            int uid = users.FindIndex(s => s == PlayerPrefsWrapper.Get(StrPrefs.input_nickname));
            if (uid == -1)
            {
                MessageBox.Error("You aren't registered. Contact administrator for additional info");
                return;
            }
            PlayerPrefsWrapper.Set(IntPrefs.sender, uid);
        }
    }


    public class out_server_info : out_signal
    {
        public Dictionary<int, out_session_info> sessions;

        public override void HandleSignal()
        {
            SessionScrollList.DrawScrollList(sessions);
        }
    }


    public class out_read_chat : out_signal
    {
        public List<chat_message> chat_buffer;

        public override void HandleSignal()
        {
            ChatScrollList.DrawScrollList(chat_buffer);
        }
    }


    public class out_write_chat : out_signal
    {
        public override void HandleSignal()
        {
            God.NetworkManager.Send(new in_read_chat());
        }
    }
    
    public class out_create_session : out_signal
    {
        public int session_id;

        public override void HandleSignal()
        {
            PlayerPrefsWrapper.Set(IntPrefs.session_id, session_id);
            God.NetworkManager.Send(new in_game_join());
        }
    }

    public class out_signal_session : out_signal
    {
        // Can't recieved
    }

    public class out_session_info : out_signal_session
    {
        public session session;
        
        public override void HandleSignal()
        {
            session?.Execute();
        }
    }
    
    public class out_game_info : out_signal_session
    {
        public abstract_game game_data;

        public override void HandleSignal()
        {
            game_data?.Execute();
        }
    }

    public class out_game_load : out_signal_session
    {
        public override void HandleSignal()
        {
            God.NetworkManager.Send(new in_game_info());
        }
    }


    public class out_game_save : out_signal_session
    {
        public abstract_game game;

        public override void HandleSignal()
        {
            if (game != null)
            {
                PlayerPrefsWrapper.Set(StrPrefs.data_save, JsonManager.Serialize(game));
                MessageBox.Info("Game saved successfully");
            }
            God.NetworkManager.Send(new in_game_info());
        }
    }

    public class out_game_join : out_signal_session
    {
        public override void HandleSignal()
        {
            UnityWrapper.LoadScene(Scenes.Session);
        }
    }


    public class out_game_quit : out_signal_session
    {
        public override void HandleSignal()
        {
            MessageBox.Info(success);
            UnityWrapper.LoadScene(Scenes.Lobby);
        }
    }


    public class out_game_play : out_signal_session
    {
        public override void HandleSignal()
        {
            God.NetworkManager.Send(new in_game_info());
        }
    }


    public class out_game_pause : out_signal_session
    {
        public override void HandleSignal()
        {
            God.NetworkManager.Send(new in_game_info());
        }
    }


    public class out_game_stop : out_signal_session
    {
        public override void HandleSignal()
        {
            God.NetworkManager.Send(new in_game_info());
        }
    }


    public class out_game_setup : out_signal
    {
        public override void HandleSignal()
        {
            Debug.Log("Setupped");
            God.NetworkManager.Send(new in_game_info());
        }
    }


    public class out_game_signal : out_signal
    {
        public override void HandleSignal()
        {
            // Nothing
        }
    }
}