/* NEXUS TECHNOLOGIES */
// SUPERIOR NETWORKS *(o. Oo. O*)
#include <ntifs.h>
#include <string>

using namespace std;

#define DEVICE_NAME L"\Device\NextUpp"
#define SYMBOLIC_NAME L"\DosDevices\NextUpp"
#define IOCTL_INDEX 0x800

#define ProtectProcess CTL_CODE(FILE_DEVICE_UNKNOWN, IOCTL_INDEX, METHOD_BUFFERED, FILE_WRITE_ACCESS)

string protected_process_name;

NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
Irp->IoStatus.Status = STATUS_SUCCESS;
Irp->IoStatus.Information = 0;
IoCompleteRequest(Irp, IO_NO_INCREMENT);
return STATUS_SUCCESS;
}

NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
Irp->IoStatus.Status = STATUS_SUCCESS;
Irp->IoStatus.Information = 0;
IoCompleteRequest(Irp, IO_NO_INCREMENT);
return STATUS_SUCCESS;
}

NTSTATUS DispatchIoctl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
switch (stack->Parameters.DeviceIoControl.IoControlCode)
{
case ProtectProcess:
protected_process_name = (char*)Irp->AssociatedIrp.SystemBuffer;
Irp->IoStatus.Status = STATUS_SUCCESS;
Irp->IoStatus.Information = 0;
break;
default:
Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
Irp->IoStatus.Information = 0;
break;
}
IoCompleteRequest(Irp, IO_NO_INCREMENT);
return Irp->IoStatus.Status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
UNICODE_STRING device_name;
RtlInitUnicodeString(&device_name, DEVICE_NAME);
IoCreateDevice(DriverObject, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &g_device_object);
DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoctl;
UNICODE_STRING symbolic_link_name;
RtlInitUnicodeString(&symbolic



