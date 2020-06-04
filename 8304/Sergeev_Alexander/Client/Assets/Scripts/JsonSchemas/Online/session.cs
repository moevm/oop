using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using GuiConcreteComponents.Lobby;
using GuiConcreteComponents.Session;
using JsonSchemas.Game;
using MonoBehaviours.Session;
using UnityEngine;
using WebSocketSharp;
// ReSharper disable InconsistentNaming
// ReSharper disable ClassNeverInstantiated.Global
// ReSharper disable UnassignedField.Global

namespace JsonSchemas.Online
{
    public class session : j_typed
    {
        public string session_name;
        public List<int> players_uid;
        public string state;
        public abstract_game game;

        public override void Execute()
        {
            if (!session_name.IsNullOrEmpty())
            {
                SessionInfoPanel.DrawPanel(this);
                PlayerPrefsWrapper.Set(StrPrefs.session_name, session_name);
                SessionBehaviour.SetSessionName(session_name);
            }
            if (players_uid != null)
            {
                PlayersScrollList.DrawScrollList(players_uid);
                SessionBehaviour.SetPlayers(players_uid);
            }
            if (!state.IsNullOrEmpty())
            {
                PlayerPrefsWrapper.Set(StrPrefs.state, state);
                SessionBehaviour.SetState(state);
            }
            if (game != null)
            {
                game.Execute();
            }
        }
    }
}