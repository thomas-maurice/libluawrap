--[[
	Exemple of pushed object, snaffle !
--]]

print("Type of Snaffle : " .. type(Snaffle))
print("Type of Snaffle.new : " .. type(Snaffle.new))
-- Create a new one
sn = Snaffle.new()
-- Let's typecheck
print("Type de sn : " .. type(sn))
-- Do snaffle
sn:doSnaffle()
print("Incrementing !")
sn:plus()
sn:plus()
print("See :")
sn:doSnaffle();
print("Change greet")
sn:setSnaffle("Kikoo")
print("See :")
print(sn:getSnaffle());
print("Do snaffle !")
sn:doSnaffle()
