#pragma once

DECLARE_LOG_CATEGORY_EXTERN(KRGDialogueRuntime, Log, All);

#define LOG_INFO(FMT, ...) UE_LOG(KRGDialogueRuntime, Display, (FMT), ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) UE_LOG(KRGDialogueRuntime, Warning, (FMT), ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) UE_LOG(KRGDialogueRuntime, Error, (FMT), ##__VA_ARGS__)
