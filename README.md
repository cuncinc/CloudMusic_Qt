# CloudMusicQt

## 开发
### 网易云音乐API
+ 地址: http://150.158.190.228:3000/
+ 文档: https://binaryify.github.io/NeteaseCloudMusicApi/
+ 手机: 16521687458
+ 密码: `16521687458.`
+ 验证码: https://www.yinsiduanxin.com/china-phone-number/verification-code-16521687458.html

### 用户

| 功能           | Method | 参数                                                         | URL                 |
| -------------- | ------ | ------------------------------------------------------------ | ------------------- |
| 手机登录       |        | `phone`: 手机号码、`password`: 密码                          | /login/cellphone    |
| 邮箱登录       |        | `email`: 163 网易邮箱、`password`: 密码                      | /login              |
| 刷新登录       |        | -                                                            | /login/refresh      |
| 发送验证码     |        | `phone`: 手机号码                                            | /captcha/sent       |
| 验证验证码     |        | `phone`: 手机号码、`captcha`: 验证码                         | /captcha/verify     |
| 注册(修改密码) |        | `captcha`: 验证码、`phone` : 手机号码、`password`: 密码、`nickname`: 昵称 | /register/cellphone |
| 退出登录       |        | -                                                            | /logout             |
| 获取用户详情   |        | `uid` : 用户 id                                              | /user/detail        |
| 获取账号详情   |        | -                                                            | /user/account       |
| 更新头像       | POST   | `mgFile`:文件                                                | /avatar/upload      |

### 歌曲

| 功能                  | Method | 参数                                                         | URL                         |
| --------------------- | ------ | ------------------------------------------------------------ | --------------------------- |
| 获取音乐 url          |        | **必选参数 :** `id` : 音乐 id、**可选参数 :** `br`: 码率,默认设置了 999000 即最大码率,如果要 320k 则可设置为 320000,其他类推 | /song/url                   |
| 歌曲详情              |        | `ids`：音乐id                                                | /song/detail                |
| 音乐是否可用          |        | `id` : 音乐 id                                               | /check/music                |
| 搜索                  |        | `keywords` : 关键字                                          | /cloudsearch                |
| 歌词                  |        | `id`：音乐id                                                 | /lyric                      |
| 每日推荐歌单          |        | -                                                            | /recommend/resource         |
| 私人FM                |        | -                                                            | /personal_fm                |
| 喜欢/取消喜欢歌曲     |        | `id`：歌曲id、`like`：bool                                   |                             |
| 云盘列表              |        | -                                                            | /user/cloud                 |
| 心动模式/智能播放列表 |        | `id` : 歌曲 id、`pid` : 歌单 id                              | /playmode/intelligence/list |
| 收藏/取消收藏歌手     |        | `id` : 歌手 id、`t`:操作,1 为收藏,其他为取消收藏             | /artist/sub                 |
| 歌手热门50首歌        |        | `id` : 歌手 id                                               | /artist/top/song            |
| 关注的歌手列表        |        |                                                              | /artist/sublist             |
| 新建歌单              |        | `name` : 歌单名、`privacy` : 是否设置为隐私歌单，默认否，传'10'则设置成隐私歌单 | /playlist/create            |
| 收藏/取消收藏歌单     |        | `id` : 歌单 id、`t` : 类型,1:收藏,2:取消收藏                 | /playlist/subscribe         |
| 歌单添加/删除歌曲     |        | `op`: 从歌单增加单曲为 add, 删除为 del、`pid`: 歌单 id 、`tracks`: 歌曲 id,可多个,用逗号隔开 | /playlist/tracks            |


### 互动

| 功能             | Method | 参数                                                         | URL                   |
| ---------------- | ------ | ------------------------------------------------------------ | --------------------- |
| 获取用户歌单     |        | `uid` : 用户 id、**可选参数 :**`limit` : 返回数量 , 默认为 30、`offset` : 偏移数量，用于分页 , 如 :( 页数 -1)*30, 其中 30 为 limit 的值 , 默认为 0、 | /user/playlist        |
| 用户历史评论     |        | `uid` : 用户 id                                              | /user/comment/history |
| 用户动态         |        | `uid` : 用户 id                                              | /user/event           |
| 关注/取消关注    |        | `id` : 用户 id、`t` : `1`为关注,其他为取消关注               | /follow               |
| 获取用户播放记录 |        | `uid` : 用户 id、**可选参数 :** `type` : type=1 时只返回 weekData, type=0 时返回 allData | /user/record          |
| 获取动态消息     |        | `pagesize` : 每页数据,默认20、`lasttime` : 返回数据的 `lasttime` ,默认-1,传入上一次返回结果的 lasttime,将会返回下一页的数据 | /event                |


### 系统

| 功能          | Method | 参数 | URL          |
| ------------- | ------ | ---- | ------------ |
| 私信&通知列表 |        |      | /msg/private |

---

#### 介绍
网易云音乐Qt版本

#### 软件架构
软件架构说明


#### 安装教程


#### 使用说明


#### 参与贡献


#### 特技
