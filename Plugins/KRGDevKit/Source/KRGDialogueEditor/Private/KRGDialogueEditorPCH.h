#pragma once

DECLARE_LOG_CATEGORY_EXTERN(KRGDialogueEditor, Log, All);

#define LOG_INFO(FMT, ...) UE_LOG(KRGDialogueEditor, Display, (FMT), ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) UE_LOG(KRGDialogueEditor, Warning, (FMT), ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) UE_LOG(KRGDialogueEditor, Error, (FMT), ##__VA_ARGS__)