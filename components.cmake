install(
	FILES
		"${DATA_DIR}/AnimatedBoundWeapons.esp"
	DESTINATION "."
	COMPONENT components
	EXCLUDE_FROM_ALL
)

install(
	FILES
		"${DATA_DIR}/AnimatedBoundWeapons.bsa"
	DESTINATION "."
	COMPONENT components
	EXCLUDE_FROM_ALL
)

install(
	FILES "${DATA_DIR}/Source/Scripts/ABW_AnimateBoundWeapon.psc"
	DESTINATION "Source/Scripts"
	COMPONENT components
	EXCLUDE_FROM_ALL
)

install(
	FILES "${DATA_DIR}/Source/Scripts/SEA_AnimateBoundWeapons.psc"
	DESTINATION "Source/Scripts"
	COMPONENT components
	EXCLUDE_FROM_ALL
)