/********************************************************************************************************
 * @file     CustomAlertView.h
 *
 * @brief    A concise description.
 *
 * @author   Telink, 梁家誌
 * @date     2021/9/16
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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

#import <UIKit/UIKit.h>
#import "CustomAlert.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^AlertResult)(CustomAlert *alertView, BOOL isConfirm);
@interface CustomAlertView : UIView

- (instancetype)initWithTitle:(NSString *)title detail:(NSString *)detail itemArray:(NSArray <AlertItemModel *>*)itemArray leftBtnTitle:(NSString *)leftBtnTitle rightBtnTitle:(NSString *)rightBtnTitle alertResult:(AlertResult) alertResult;

- (void)showCustomAlertView;

@end

NS_ASSUME_NONNULL_END
