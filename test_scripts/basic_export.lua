--[[
    File: basic_export.lua
    Author: Thomas Maurice
    
    Here is the corresponding file to read C++ exported variables
    from Lua. As you see it is very simple: just call them by their names.
    
    They will be accessibles as soon as they will be exported into the Lua context.
--]]

print("Exported number 'num' :", num)
print("Exported string 'str' :", str)
