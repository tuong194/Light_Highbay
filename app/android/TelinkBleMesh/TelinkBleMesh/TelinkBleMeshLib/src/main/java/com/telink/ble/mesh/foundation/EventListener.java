/********************************************************************************************************
 * @file EventListener.java
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

package com.telink.ble.mesh.foundation;

/**
 * This interface allows for a flexible and extensible event handling mechanism, where different classes can implement the "EventListener" interface to handle events of different types.
 *
 * @param <T>
 */
public interface EventListener<T> {

    /**
     * This method should be implemented by these classes to define the logic for handling the event.
     *
     * @param event target event
     */
    void performed(Event<T> event);
}