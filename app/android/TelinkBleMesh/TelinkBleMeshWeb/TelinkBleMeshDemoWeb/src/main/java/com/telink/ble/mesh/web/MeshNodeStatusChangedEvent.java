/********************************************************************************************************
 * @file MeshNodeStatusChangedEvent.java
 *
 * @brief for TLSR chips
 *
 * @author telink
 * @date Sep. 30, 2017
 *
 * @par Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/
package com.telink.ble.mesh.web;

import android.os.Parcel;
import android.os.Parcelable;

import com.telink.ble.mesh.foundation.Event;
import com.telink.ble.mesh.model.NodeInfo;
import com.telink.ble.mesh.web.entity.MeshNode;

/**
 * Created by kee on 2019/9/18.
 */

public class MeshNodeStatusChangedEvent extends Event<String> implements Parcelable {
    public static final String EVENT_TYPE_NODE_STATUS_CHANGED = "com.telink.ble.mesh.EVENT_TYPE_NODE_STATUS_CHANGED";
    private MeshNode nodeInfo;

    public MeshNodeStatusChangedEvent(Object sender, String type, MeshNode nodeInfo) {
        super(sender, type);
        this.nodeInfo = nodeInfo;
    }

    protected MeshNodeStatusChangedEvent(Parcel in) {
    }

    public static final Creator<MeshNodeStatusChangedEvent> CREATOR = new Creator<MeshNodeStatusChangedEvent>() {
        @Override
        public MeshNodeStatusChangedEvent createFromParcel(Parcel in) {
            return new MeshNodeStatusChangedEvent(in);
        }

        @Override
        public MeshNodeStatusChangedEvent[] newArray(int size) {
            return new MeshNodeStatusChangedEvent[size];
        }
    };

    public MeshNode getNodeInfo() {
        return nodeInfo;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
    }
}
