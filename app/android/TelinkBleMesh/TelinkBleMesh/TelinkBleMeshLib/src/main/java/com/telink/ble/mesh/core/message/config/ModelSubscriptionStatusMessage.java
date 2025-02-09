/********************************************************************************************************
 * @file ModelSubscriptionStatusMessage.java
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
package com.telink.ble.mesh.core.message.config;

import android.os.Parcel;
import android.os.Parcelable;

import com.telink.ble.mesh.core.MeshUtils;
import com.telink.ble.mesh.core.message.StatusMessage;

import java.nio.ByteOrder;

/**
 * The Config Model Subscription Status is an unacknowledged message used to report a status of the operation on the Subscription List
 */

/**
 * The ModelSubscriptionStatusMessage class represents an unacknowledged message used to report the status of an operation on the Subscription List in the Config Model.
 */
public class ModelSubscriptionStatusMessage extends StatusMessage implements Parcelable {
    private static final int DATA_LEN_SIG = 7;
    private static final int DATA_LEN_VENDOR = 9;
    private byte status;
    private int elementAddress;
    /**
     * The group address.
     */
    private int address;
    /**
     * The model identifier, which can be 2 or 4 bytes determined by whether it is a SIG or vendor model.
     */
    private int modelIdentifier;
    /**
     * Indicates whether the model is a SIG or vendor model.
     */
    private boolean isSig = true;

    /**
     * Constructs a new ModelSubscriptionStatusMessage object.
     */
    public ModelSubscriptionStatusMessage() {
    }

    /**
     * Constructs a new ModelSubscriptionStatusMessage object from a Parcel.
     *
     * @param in The Parcel object to read the data from.
     */
    protected ModelSubscriptionStatusMessage(Parcel in) {
        status = in.readByte();
        elementAddress = in.readInt();
        address = in.readInt();
        modelIdentifier = in.readInt();
        isSig = in.readByte() != 0;
    }

    /**
     * A Creator object that is used to create new instances of the ModelSubscriptionStatusMessage class from a Parcel.
     */
    public static final Creator<ModelSubscriptionStatusMessage> CREATOR = new Creator<ModelSubscriptionStatusMessage>() {
        @Override
        public ModelSubscriptionStatusMessage createFromParcel(Parcel in) {
            return new ModelSubscriptionStatusMessage(in);
        }

        @Override
        public ModelSubscriptionStatusMessage[] newArray(int size) {
            return new ModelSubscriptionStatusMessage[size];
        }
    };

    /**
     * Parses the byte array to populate the fields of the ModelSubscriptionStatusMessage object.
     *
     * @param params The byte array containing the data to parse.
     */
    @Override
    public void parse(byte[] params) {
        isSig = params.length == DATA_LEN_SIG;
        int index = 0;
        status = params[index++];
        elementAddress = MeshUtils.bytes2Integer(params, index, 2, ByteOrder.LITTLE_ENDIAN);
        index += 2;
        address = MeshUtils.bytes2Integer(params, index, 2, ByteOrder.LITTLE_ENDIAN);
        index += 2;
        modelIdentifier = MeshUtils.bytes2Integer(params, index, isSig ? 2 : 4, ByteOrder.LITTLE_ENDIAN);
    }

    /**
     * Returns a bitmask indicating the set of special object types marshaled by this Parcelable object instance.
     *
     * @return Always returns 0.
     */
    @Override
    public int describeContents() {
        return 0;
    }

    /**
     * Flattens the ModelSubscriptionStatusMessage object into a Parcel.
     *
     * @param dest  The Parcel object to write the flattened object to.
     * @param flags Additional flags about how the object should be written.
     */
    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeByte(status);
        dest.writeInt(elementAddress);
        dest.writeInt(address);
        dest.writeInt(modelIdentifier);
        dest.writeByte((byte) (isSig ? 1 : 0));
    }

    /**
     * Returns the status of the operation.
     *
     * @return The status of the operation.
     */
    public byte getStatus() {
        return status;
    }

    /**
     * Returns the element address.
     *
     * @return The element address.
     */
    public int getElementAddress() {
        return elementAddress;
    }

    /**
     * Returns the group address.
     *
     * @return The group address.
     */
    public int getAddress() {
        return address;
    }

    /**
     * Returns the model identifier.
     *
     * @return The model identifier.
     */
    public int getModelIdentifier() {
        return modelIdentifier;
    }

    /**
     * Returns whether the model is a SIG model or a vendor model.
     *
     * @return True if the model is a SIG model, false if it is a vendor model.
     */
    public boolean isSig() {
        return isSig;
    }

    /**
     * Returns a string representation of the ModelSubscriptionStatusMessage object.
     *
     * @return A string representation of the ModelSubscriptionStatusMessage object.
     */
    @Override
    public String toString() {
        return "ModelSubscriptionStatusMessage{" +
                "status=" + status +
                ", elementAddress=" + elementAddress +
                ", address=" + address +
                ", modelIdentifier=" + modelIdentifier +
                ", isSig=" + isSig +
                '}';
    }
}