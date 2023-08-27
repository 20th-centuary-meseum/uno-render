#include "controller.hpp"

byte con1 = 0;
byte con2 = 0;

void init_controller()
{
	pinMode(CON1_A_PIN, INPUT);
	pinMode(CON1_B_PIN, INPUT);

	pinMode(CON1_AT_PIN, INPUT);

	pinMode(CON1_U_PIN, INPUT);
	pinMode(CON1_R_PIN, INPUT);
	pinMode(CON1_D_PIN, INPUT);
	pinMode(CON1_L_PIN, INPUT);

	pinMode(CON2_A_PIN, INPUT);
	pinMode(CON2_B_PIN, INPUT);

	pinMode(CON2_AT_PIN, INPUT);

	pinMode(CON2_U_PIN, INPUT);
	pinMode(CON2_R_PIN, INPUT);
	pinMode(CON2_D_PIN, INPUT);
	pinMode(CON2_L_PIN, INPUT);
}

void update_controller()
{
	con1 = digitalRead(CON1_A_PIN) << A_BIT |
		   digitalRead(CON1_B_PIN) << B_BIT |

		   digitalRead(CON1_AT_PIN) << AT_BIT |

		   digitalRead(CON1_U_PIN) << U_BIT |
		   digitalRead(CON1_R_PIN) << R_BIT |
		   digitalRead(CON1_D_PIN) << D_BIT |
		   digitalRead(CON1_L_PIN) << L_BIT;

	con2 = digitalRead(CON2_A_PIN) << A_BIT |
		   digitalRead(CON2_B_PIN) << B_BIT |

		   digitalRead(CON2_AT_PIN) << AT_BIT |

		   digitalRead(CON2_U_PIN) << U_BIT |
		   digitalRead(CON2_R_PIN) << R_BIT |
		   digitalRead(CON2_D_PIN) << D_BIT |
		   digitalRead(CON2_L_PIN) << L_BIT;
}