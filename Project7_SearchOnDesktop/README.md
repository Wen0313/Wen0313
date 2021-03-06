写在前面
	※中文首字母匹配和搜索结果列表优化一项描述的较详细，因为对于展示结果很关键

2021.7.26
	※添加了一项功能：所有文件名会在程序启动时保存在内存(QStringList)里
	※完成了启动项：程序启动时默认展示用户桌面下所有文件和文件夹信息

2021.7.27
	※添加了一项功能：右键菜单（打开/删除）
		※删除将直接删除，不会进入回收站（后来加了删除提示）
	※添加了一项功能：目录监控，现在外面操作文件（增删重命名）程序也会响应了
		※会根据搜索框的内容展示，符合预期的才会展示
		※一次性新增或删除多个文件/文件夹时也可以正确响应
	※添加了一项功能：模糊匹配

2021.7.28
	※修复了一个bug，该bug曾导致：如果选择打开了一个ppt或doc等使用wps打开的文件，那么桌面会生成一个~$开头的隐藏备份文件，这时目录
		监控会发现它，但是entryList函数即使读不到这个隐藏文件名size却会加1，程序会进入死循环进而崩溃。
	※优化了一项功能：现在右键删除的时候会有提示信息了，选择yes才会永久删除文件
	※添加了一项功能：中文首字母匹配
		※仅从桌面文件的名字的【第0位】开始匹配，如果第0位不匹配那么检索结果不显示，例如输入"sjs"不能检索到"金山"
		※【不区分】大小写，例如输入"JS"或者"Js"等都能检索到"金山"
		※值得一提的是，参考自己的搜索习惯，首字母匹配可以从开头一直匹配下一位，且不仅限于纯中文名称，只要【当前匹配成功】则
			显示结果，例如输入"js"可以检索到"金山会议"与"金山WPS"等名称。但【特别注意】，首字母匹配一定是从第0位开始的
	※添加了一项功能：搜索结果列表优化，现在匹配度更高的将优先展示在上面了
		※第一级是完全匹配
			※【注意】：完全匹配是【区分】大小写的，不然就不叫完全匹配了，例如输入"js","JS"这个名字算作完全包含一级
			※基于完全匹配特性，内部不存在优先级
		※第二级是首字母匹配
			※第二级【内部优先级】为：文件名长度（上面功能描述中解释了为什么首字母匹配会有内部优先级，也即从第0位开始
				可以继续往后匹配）
			※上面有提到首字母匹配是不区分大小写的，也即如果输入的内容与文件名大小写不能完全匹配，那中文首字母匹配将
				【优先级更高】，例如输入"js"，"金山"的优先级将比"JS"或"Js"等更高
			※需要说明的是，如果中文名称首字母不匹配那么不会继续模糊匹配，例如输入"JS.T"可以检索出"金山.txt"但是"JST"则不能
		※第三级是完全包含
			※第三级【内部优先级】为：text出现的位置>文件名长度
			※也即在完全包含的情况下，text出现的位置更早的将优先展示，例如输入"jshy","ajshyaaa"将【必然】展示在"aajshy"之前
				（出现位置更早），且"aajshy"【必然】展示在"aajshya"之前（出现位置相同名字更短）
		※第四级是模糊匹配
			※第四级【内部优先级】为：匹配到text之间的间隔距离>text首字母出现的位置>文件名长度
			※例如输入"jshy"，"jshxxy"将【必然】在"aaajshay"之后（虽然匹配的首字母出现更早，但间隔距离xx比a大）、在"aajshaay"
				之前（间隔相等但前者在0位置匹配到）、在"jshxxyyy"之前（后者名字更长）
		※【特别注意】鉴于只有在完全匹配的时候重视大小写，其他时候匹配是忽略大小写的，所以展示结果中二三四级【内部的优先级】依然
			忽略了大小写的影响
		※【特别注意】现在外部操作时目录监控响应在列表中也可以正确显示出优先级了，包括【批量操作】

2021.7.29
	※修复了一个bug，该bug曾导致：在搜索框有内容且列表已经展示的情况下桌面新增或重命名了能匹配上的文件时该条信息不能
		正确的显示在合适的行数
	※优化了一处程序：鉴于在修复上面bug的过程中文件监控响应函数里要匹配优先级，这会出现两大段的代码复用，所以把选择
		插入行数的功能加在了插入函数insertToTable里面，那么就不用在各个涉及到优先级的地方使用一段为了找
		合适的行数的基本相同的代码了
	※优化了一项功能：现在同时选择多个文件后点击右键菜单的打开或删除都能正确响应【所有条目】了，并且点击删除时弹出的
		消息提示中可以正确显示待删除内容了
	※优化了一项功能：作为重中之重的结果优化算法，现在该功能中的分级【内部】也有优先级了【细节已更新在上面功能描述中】
	※添加了一项功能：程序启动默认隐藏，注册了Alt+Space热键，按下可以唤出窗口，或者窗口显示的时候按下可以隐藏窗口

2021.7.30
	※修复了一个bug，该bug曾导致：使用右键批量删除的时候目录监控会响应多次（删除几条就响应几次），即使响应函数
		一次性就可以完成所有更新内容，于是后续操作文件时会出现错误
	※修复了一个bug，该bug曾导致：在界面空白处右键唤出菜单后点击选项会出现期待之外的响应事件，甚至点击重命名时
		程序会直接崩溃
	※添加了一项功能：双击鼠标左键打开文件（且在整行的任意位置双击都能正确打开文件）
	※添加了一项功能：右键菜单添加了【重命名】操作
		※新建了一个窗口类，当选择重命名的时候会调用它。值得一提的是，弹窗的输入框中会默认显示当前文件/文件夹的原名字
		※预期的各种修改失败的情况能正确显示错误信息，该功能不支持批量操作

2021.7.31
	※优化了一项功能：现在删除失败的时候会有提示信息了（包括批量删除时删除失败的错误）