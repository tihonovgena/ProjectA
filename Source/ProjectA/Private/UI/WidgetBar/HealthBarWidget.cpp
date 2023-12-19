// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "UI/WidgetBar/HealthBarWidget.h"
#include "Interface/HealthComponentInterface.h"

float UHealthBarWidget::GetHealthPercent() const
{
	IHealthComponentInterface* HealthComponentInterface = Cast<IHealthComponentInterface>(GetOwningPlayerPawn());
	if (HealthComponentInterface)
	{
		return HealthComponentInterface->GetHealthPercent();
	}
	return 0.f;
	
}
