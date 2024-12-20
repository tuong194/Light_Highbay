/********************************************************************************************************
 * @file     ChooseOOBFileVC.m
 *
 * @brief    for TLSR chips
 *
 * @author   Telink, 梁家誌
 * @date     2020/5/12
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

#import "ChooseOOBFileVC.h"
#import "ChooseBinCell.h"
#import "UIViewController+Message.h"

@interface ChooseOOBFileVC ()<UITableViewDelegate,UITableViewDataSource>
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UIButton *importButton;
@property (nonatomic, assign) int selectIndex;
@property (nonatomic,strong) NSMutableArray <NSString *>*source;

@end

@implementation ChooseOOBFileVC

- (IBAction)clickImportFile:(UIButton *)sender {
    if (self.selectIndex == -1) {
        [self showTips:@"please choose oob file!"];
        return;
    }
    NSString *fileName = self.source[self.selectIndex];
    NSData *fileData = [self getDataWithFileName:fileName];
    if (fileData == nil || fileData.length == 0) {
        [self showTips:@"this oob file is empty, please choose other!"];
        return;
    }

    if (self.backOobFileInfo) {
        self.backOobFileInfo(fileData,fileName);
    }

    [self.navigationController popViewControllerAnimated:YES];
}

- (void)normalSetting{
    [super normalSetting];
    self.importButton.backgroundColor = UIColor.telinkButtonBlue;
    self.title = @"File Selector";
    self.selectIndex = -1;
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    [self.tableView registerNib:[UINib nibWithNibName:CellIdentifiers_ChooseBinCellID bundle:nil] forCellReuseIdentifier:CellIdentifiers_ChooseBinCellID];

    self.source = [NSMutableArray array];
    //搜索Documents(通过iTunes File 加入的文件需要在此搜索)
    NSFileManager *mang = [NSFileManager defaultManager];
    NSError *error = nil;
    NSString *fileLocalPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSArray *fileNames = [mang contentsOfDirectoryAtPath:fileLocalPath error:&error];
    for (NSString *path in fileNames) {
        //本地512k的存储文件名为“test.bin”，不可用于OTA
        if ([path containsString:@".txt"]) {
            [self.source addObject:path];
        }
    }
}

- (NSData *)getDataWithFileName:(NSString *)fileName{
    //通过iTunes File 加入的文件
    NSString *fileLocalPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    fileLocalPath = [NSString stringWithFormat:@"%@/%@",fileLocalPath,fileName];
    NSError *err = nil;
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingFromURL:[NSURL URLWithString:fileLocalPath] error:&err];
    NSData *data = fileHandle.readDataToEndOfFile;
    return data;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    ChooseBinCell *cell = (ChooseBinCell *)[tableView dequeueReusableCellWithIdentifier:CellIdentifiers_ChooseBinCellID forIndexPath:indexPath];
    NSString *binString = self.source[indexPath.row];
    cell.nameLabel.text = binString;
    cell.selectButton.selected = indexPath.row == self.selectIndex;
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.source.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 44.0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (indexPath.row == self.selectIndex) {
        self.selectIndex = -1;
    } else {
        self.selectIndex = (int)indexPath.row;
    }
    [self.tableView reloadData];
}

-(void)dealloc{
    TelinkLogDebug(@"");
}

@end
