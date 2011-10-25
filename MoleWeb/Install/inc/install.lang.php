<?php
if(!defined('LIUCMS_INSTALL')) exit('Access Denied');
$lang = array(
	'install_is_lock' => '你的网站已经安装过MoleWeb，需重新安装请手动删除网站目录下Public/Data/install.lock文件', 
	'install_db_error' => '数据库文件无法读取，请检查/install/moleweb.com.sql是否存在。',
	'install_title' => 'MoleWeb 1.0 正式版 安装向导',
	'welcome_to_install' => '欢迎安装',
	'install_wizard' => '安装向导',
	'install_error' => '安装出错',
	'install_tips' => '注意',
	'install_tips_content' => '这个安装程序仅仅用在你首次安装MoleWeb。如果你已经在使用 MoleWeb 或者要更新到一个新版本，请不要运行这个安装程序。',
	'install_notes' => '安装须知',
	'install_notes_content' => '<p>一、运行环境需求：PHP(5.2.0+)+MYSQL(4.1+)</p><p>二、安装步骤：<br />1、使用ftp工具以二进制模式，将该软件包里的 MoleWeb 目录及其文件上传到您的空间，假设上传后目录仍旧为 MoleWeb<br />2、如果您使用的是Linux 或 Freebsd 服务器，先确认以下目录或文件属性为 (777) 可写模式。<br />目录: Public/Data<br />目录: Install<br />文件: config.inc.php<br />3、运行 http://yourwebsite/MoleWeb/Install/index.php 安装程序，填入安装相关信息与资料，完成安装！<br />4、运行 http://yourwebsite/MoleWeb/index.php 开始体验MoleWeb1.0正式版！<br />5、如安装完成后访问异常，请手动删除Admin/Runtime和LiuCmsApp/Runtime目录下所有文件。</p>',
	'install_license' => '安装许可协议',
	'install_license_content' => '
版权所有 (C) 2010，MoleWeb 保留所有权利。

Mole2d 独立游戏创作平台
  ~~~~~~~~~~~~~~~~~~
  使用和发布许可
  ~~~~~~~~~~~~~~

       Mole2d 独立游戏创作平台 采用“商业用户付款，其它用户免费”的方式发布。
  这意味着：

  1. 所有的 Mole2d 独立游戏创作平台 版权专属于作者 欧云辉 所有。

  2. 任何人都可以在不做为商业赢利模式下使用 Mole2d 独立游戏创作平台 ，如果您
     想在商业模式下使用本软件，需与作者本人联系，获得一个商业许可协议。

  3. Mole2d 独立游戏创作平台 的许可类型是：

     a. 非商业用户。用户可以任意的使用本软件，但请不要有任何的商业用途。

     b. 商业用户。用户购买与其计算机相同数量的使用授权来使用。


     当注册完成后，对于任何合法购买，用户被授予非唯一的许可，在和根据上面记
     录购买的许可数量相同的数目的计算机上使用 Mole2d 独立游戏创作平台。已注
     册的 Mole2d 独立游戏创作平台 软件不可以出租或租借，但是如果接收人同意
     遵守此许可条款，可以永久完全转让。如果软件更新，转让者必须包含更新和所
     有以前的版本。

  4. 要购买商业版本请查看 order.htm 的详细信息。

  5. Mole2d 独立游戏创作平台 是自愿使用的形式。没有任何明确或暗示形式的担保。您
     必须自己承担使用的风险。不管是作者还是作者的代理，都没有责任对使用或误
     用本软件时的数据丢失、损坏、利益损失或其它任何形式的损失负责。

  6. 用户可以使用 Mole2d 独立游戏创作平台 创作各种游戏，非商业用户可以做非商业
     用途的游戏发布，商业用户可以销售用 Mole2d 独立游戏创作平台 制作的游戏。

  7. 除了在本协议中许可的条件外，你不可以使用、复制、模仿、拷贝、租借、出租、
     出售、修改、反编译、反汇编、其它的反向工程，或者转让被许可的程序，或者
     被许可程序的任何子集，任何未经授权的使用都将导致立即的和自动的许可协议
     的终止，并且可能导致刑事和/或民事诉讼的结果。

     Mole2d 独立游戏创作平台 的二进制代码不可以在没有作者的书面许可的情况下被使
     用或进行反向工程来重建，该软件为作者所有。

     在没有获得版权所有者的书面许可下，Mole2d 独立游戏创作平台 的注册文件除了
     第三条描述的情况外，不能被分发到原始购买人合法控制的人及区域之外。

     所有在这里没有明确规定的权利，由 欧云辉 保留。

  8. 安装并使用 Mole2d 独立游戏创作平台 即表示接受上述使用条款及许可条件。

  9. 如果你不同意这个许可中的条款，你必须从你的存储设备中删除 Mole2d 独立游戏创
      作平台 文件并终止使用本产品。

      感谢使用原版 Mole2d 独立游戏创作平台。

',
	'install_agree' => '我已看过并同意安装许可协议',
	'install_disagree_license' => '您必须在同意授权协议的全部条件后，方可继续MoleWeb的安装',
	'install_env' => '服务器配置',
	'php_os' => '操作系统',
	'php_version' => 'PHP版本',
	'file_upload' => '附件上传',
	'php_extention' => 'PHP扩展',
	'php_extention_unload_gd' => '您的服务器没有安装这个PHP扩展：gd',
	'php_extention_unload_mbstring' => '您的服务器没有安装这个PHP扩展：mbstring',
	'php_extention_unload_mysql' => '您的服务器没有安装这个PHP扩展：mysql',
	'php_extention_unload_curl' => '您的服务器没有安装这个PHP扩展：curl',
	'mysql' => 'MySQL数据库',
	'mysql_unsupport' => '您的服务器不支持MYSQL数据库，无法安装MoleWeb。',
	'dirmod' => '目录和文件属性',
	'install_setting' => '数据库和网站设置',
	'install_mysql_host' => '数据库地址',
	'install_mysql_host_intro' => '格式：地址(:端口)，一般为 localhost',
	'install_mysql_username' => '数据库用户名',
	'install_mysql_password' => '数据库密码',
	'install_mysql_name' => '数据库名',
	'install_mysql_prefix' => '表名前缀',
	'install_mysql_prefix_intro' => '同一数据库安装多MoleWeb程序时可改变默认值',
	'founder' => '创始人设置',
	'install_founder_name' => '创始人账号',
	'install_founder_password' => '密码',
	'install_founder_rpassword' => '重复密码',
	'install_founder_email' => '电子邮件',
	'site_url' => '网站域名',
	'site_url_intro' => '将作为网站首页的地址',
	'install_mysql_host_empty' => '数据库服务器不能为空',
	'install_mysql_username_empty' => '数据库用户名不能为空',
	'install_mysql_name_empty' => '数据库名不能为空',
	'install_founder_name_empty' => '创始人用户名不能为空',
	'install_founder_password_length' => '创始人密码必须大于6位',
	'install_founder_rpassword_error' => '两次输入管理员密码不同',
	'install_founder_email_empty' => '创始人Email不能为空',
	'mysql_invalid_configure' => '数据库配置信息不完整',
	'mysql_invalid_prefix' => '您指定的数据表前缀包含点字符(".")，请返回修改。',
	'forbidden_character' => '用户名包含非法字符',
	'founder_invalid_email' => '电子邮件格式不正确',
	'founder_invalid_configure' => '创始人信息不完整',
	'founder_invalid_password' => '密码长度必须大于6位',
	'founder_invalid_rpassword' => '两次输入的密码不一致',
	'config_log_success' => '数据库配置信息写入完成',
	'config_read_failed' => '数据库配置文件写入错误，请检查config.inc.php文件是否存在或属性是否为777',
	'liucms_rebuild' => '数据库中已经安装过 MoleWeb，继续安装会清空原有数据！',
	'mysql_import_data' => '点击下一步开始导入数据',
	'import_processing' => '导入数据库',
	'import_processing_error' => '导入数据库失败',
	'create_table' => '创建表',
	'create_founder' => '创建创始人帐户',
	'create_founder_success' => '创始人帐户创建成功',
	'create_founder_error' => '创始人帐户创建失败',
	'install_success' => '安装成功',
	'install_failure' => '安装失败',
	'reinstall' => '<a href="index.php">请点击这里重新安装</a>',
	'install_success_intro' => '安装程序执行完毕，请尽快删除整个 install 目录，以免被他人恶意利用。如要重新安装，请删除本目录的 install.lock 文件！<br /><a href="../index.php">请点击这里开始体验MoleWeb吧！</a>',
	'install_dbFile_error' => '数据库文件无法读取，请检查/install/inc/MoleWeb.com.sql是否存在。',
	
	'install_step_wizard' => '安装向导',
	'install_step_notes' => '安装须知',
	'install_step_license' => '许可协议',
	'install_step_os' => '环境检测',
	'install_step_option' => '安装配置',
	'install_step_config' => '写入配置',
	'install_step_import' => '导入数据',
	'install_step_finish' => '安装完成',
	
	'install_btn_start' => '开始安装MoleWeb！',
	'install_btn_prev' => '上一步',
	'install_btn_next' => '下一步',
	'go_home' => '前往前台',
	'go_admin' => '前往后台',
	'support' => '支持',
	'unsupport' => '不支持',
);
?>