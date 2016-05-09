---
layout: post
title: uaa scope  
tags: cloudfoundry
categories: work experience
---

### token管理

tokens.write：token除权，包括用户和客户端token
tokens.read：token读取，包括用户和客户端token

### UAA用户组管理

scim.read：读用户和组
 scim.write：添加/更新/删除用户和组
 password.write：修改自己的密码
 scim.userids：访问用户 ids/user的endpoint
 scim.me：读/添加/更新/删除自己的用户和组
 uaa.admin：设置用户密码

### UAA客户端管理

clients.read：读取客户端注册信息
 clients.write：添加，更新，删除客户端
 clients.secret：修改自己的密钥

### 杂项

openid：SSO（Single Sign On）时，获取用户信息
 uaa.admin：设置用户密码
 uaa.user：用户都拥有的权限，尚未用到
 uaa.resource：未用到
 approvals.me：未用到
 CloudController访问
 cloud\_controller.admin：管理访问，包含读和写
 cloud\_controller.read：读权限，一般指GET请求
 cloud\_controller.write：写权限， 一般指POST，PUT，DELETE请求，但同时需要OrgManger角色。
  
  添加一个用户后，uaa会给一些默认权限：openid, password.write, cloud\_controller.read, cloud\_controller.write, tokens.read, tokens.write，这些权限无需显示添加。
  注意：cf版本之间有微小的差异，例如：cloud\_controller.write在某些版本还是不支持的，应用时需注意具体情况。
