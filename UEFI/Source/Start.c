#include <efi.h>
#include <efilib.h>
 
EFI_STATUS EFIStart(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
 
    /* Store the system table for future use in other functions */
    ST = SystemTable;
 
    Status = ST->ConOut->SetAttribute(ST->ConOut, 0x40);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    /* Say hi */
    Status = ST->ConOut->OutputString(ST->ConOut, L"YOOO MANG!!!!!\n\r");
    if (EFI_ERROR(Status))
        return Status;

    Status = ST->ConOut->OutputString(ST->ConOut, L"Framebuffer base is at x");

    /* Now wait for a keystroke before continuing, otherwise your
       message will flash off the screen before you see it.
 
       First, we need to empty the console input buffer to flush
       out any keystrokes entered before this point */
    Status = ST->ConIn->Reset(ST->ConIn, FALSE);
    if (EFI_ERROR(Status))
        return Status;
 
    /* Now wait until a key becomes available.  This is a simple
       polling implementation.  You could try and use the WaitForKey
       event instead if you like */
    while ((Status = ST->ConIn->ReadKeyStroke(ST->ConIn, &Key)) == EFI_NOT_READY) ;
 
    return Status;
}