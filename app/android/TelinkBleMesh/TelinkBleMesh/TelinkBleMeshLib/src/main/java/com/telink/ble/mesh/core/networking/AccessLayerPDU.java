/********************************************************************************************************
 * @file AccessLayerPDU.java
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
package com.telink.ble.mesh.core.networking;

/**
 * access payload
 * Created by kee on 2019/7/29.
 */

import com.telink.ble.mesh.core.MeshUtils;
import com.telink.ble.mesh.core.message.OpcodeType;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * This class represents a PDU (Protocol Data Unit) for the Access Layer in a networking protocol.
 * An access payload may be sent in up to 32 segments of 12 octets each.
 * This implies that the maximum number of octets is 384 including the TransMIC
 * <p>
 * 12 * 32
 * packet-len * packet-cnt
 * <p>
 * transMIC 4 bytes
 * at least 1 byte opcode
 */
public class AccessLayerPDU implements NetworkingPDU {
    // 1, 2 or 3 bytes
    public int opcode;

    // 0 ~ 379 bytes
    public byte[] params;

//    public byte[] decryptedPayload;

    /**
     * Private constructor to prevent direct instantiation of the class.
     */
    private AccessLayerPDU() {
    }

    /**
     * Constructs an AccessLayerPDU object with the given opcode and params.
     *
     * @param opcode The opcode value of the PDU.
     * @param params The parameters of the PDU.
     */
    public AccessLayerPDU(int opcode, byte[] params) {
        this.opcode = opcode;
        this.params = params;
    }

    /**
     * Parses the given payload byte array and returns an AccessLayerPDU object.
     *
     * @param payload The payload byte array to be parsed.
     * @return An AccessLayerPDU object representing the parsed payload.
     */
    public static AccessLayerPDU parse(byte[] payload) {
        AccessLayerPDU accessPDU = new AccessLayerPDU();
        OpcodeType opType = OpcodeType.getByFirstByte(payload[0]);

        accessPDU.opcode = 0;
        int index = 0;
        for (int i = 0; i < opType.length; i++) {
            accessPDU.opcode |= (payload[index++] & 0xFF) << (8 * i);
        }

        final int paramLen = payload.length - opType.length;
        accessPDU.params = new byte[paramLen];
        System.arraycopy(payload, index, accessPDU.params, 0, paramLen);
        return accessPDU;
    }


    /**
     * Converts the AccessLayerPDU object to a byte array.
     *
     * @return A byte array representing the AccessLayerPDU object.
     */
    @Override
    public byte[] toByteArray() {
        int opcodeLen = OpcodeType.getByFirstByte((byte) opcode).length;
        if (params == null || params.length == 0) {
            return MeshUtils.integer2Bytes(opcode, opcodeLen, ByteOrder.LITTLE_ENDIAN);
        } else {
            return ByteBuffer.allocate(opcodeLen + params.length).order(ByteOrder.LITTLE_ENDIAN)
                    .put(MeshUtils.integer2Bytes(opcode, opcodeLen, ByteOrder.LITTLE_ENDIAN))
                    .put(params)
                    .array();
        }
    }
}
