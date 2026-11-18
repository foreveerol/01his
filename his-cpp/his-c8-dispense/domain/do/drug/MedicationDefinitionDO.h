#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: tanqian
 @Date: 2026/07/26 10:00:00

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _MEDICATION_DEFINITION_DO_
#define _MEDICATION_DEFINITION_DO_
#include "../DoInclude.h"

/**
 * Medication definition database entity (med_medication_definition table)
 * Represents a medication/drug definition in the hospital information system
 */
class MedicationDefinitionDO : public BaseDO
{
	// Common audit fields
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	MYSQL_SYNTHESIZE(string, updated_at, UpdatedAt);
	MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
	MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
	MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
	MYSQL_SYNTHESIZE(string, deleted_at, DeletedAt);
	MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);

	// Business fields
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, domain_enum, DomainEnum);
	MYSQL_SYNTHESIZE(string, med_version, MedVersion);
	MYSQL_SYNTHESIZE(string, name_en, NameEn);
	MYSQL_SYNTHESIZE(string, py_str, PyStr);
	MYSQL_SYNTHESIZE(string, wb_str, WbStr);
	MYSQL_SYNTHESIZE(string, category_code, CategoryCode);
	MYSQL_SYNTHESIZE(string, merchandise_name, MerchandiseName);
	MYSQL_SYNTHESIZE(string, merchandise_py_str, MerchandisePyStr);
	MYSQL_SYNTHESIZE(string, merchandise_wb_str, MerchandiseWbStr);
	MYSQL_SYNTHESIZE(string, purchase_unit_code, PurchaseUnitCode);
	MYSQL_SYNTHESIZE(string, split_unit_code, SplitUnitCode);
	MYSQL_SYNTHESIZE(string, comprised_text, ComprisedText);
	MYSQL_SYNTHESIZE(string, ingredient, Ingredient);
	MYSQL_SYNTHESIZE(int, dose_from, DoseFrom);
	MYSQL_SYNTHESIZE(string, approval_number, ApprovalNumber);
	MYSQL_SYNTHESIZE(int, yb_match_flag, YbMatchFlag);
	MYSQL_SYNTHESIZE(string, yb_no, YbNo);
	MYSQL_SYNTHESIZE(string, pharmacology_category_code, PharmacologyCategoryCode);
	MYSQL_SYNTHESIZE(int, skin_test_flag, SkinTestFlag);
	MYSQL_SYNTHESIZE(int, inject_flag, InjectFlag);
	MYSQL_SYNTHESIZE(string, manufacturer_id, ManufacturerId);
	MYSQL_SYNTHESIZE(string, manufacturer_text, ManufacturerText);
	MYSQL_SYNTHESIZE(string, supply_id, SupplyId);
	MYSQL_SYNTHESIZE(int, restricted_flag, RestrictedFlag);
	MYSQL_SYNTHESIZE(string, restricted_scope, RestrictedScope);
	MYSQL_SYNTHESIZE(int, active_flag, ActiveFlag);
	MYSQL_SYNTHESIZE(int, children_flag, ChildrenFlag);
	MYSQL_SYNTHESIZE(int, characteristic, Characteristic);
	MYSQL_SYNTHESIZE(double, item_min_quantity, ItemMinQuantity);
	MYSQL_SYNTHESIZE(double, item_max_quantity, ItemMaxQuantity);
	MYSQL_SYNTHESIZE(string, def_encounter_unit_code, DefEncounterUnitCode);
	MYSQL_SYNTHESIZE(string, def_inhospital_unit_code, DefInhospitalUnitCode);
	MYSQL_SYNTHESIZE(string, national_drug_code, NationalDrugCode);
	MYSQL_SYNTHESIZE(string, part_attribute_enum, PartAttributeEnum);
	MYSQL_SYNTHESIZE(string, antibiotic_code, AntibioticCode);
	MYSQL_SYNTHESIZE(string, restricted_enum, RestrictedEnum);
	MYSQL_SYNTHESIZE(int, self_flag, SelfFlag);
	MYSQL_SYNTHESIZE(int, antibiotic_flag, AntibioticFlag);
	MYSQL_SYNTHESIZE(int, basic_flag, BasicFlag);
	MYSQL_SYNTHESIZE(string, tho_part_attribute_enum, ThoPartAttributeEnum);
	MYSQL_SYNTHESIZE(int, chrgitm_lv, ChrgitmLv);
	MYSQL_SYNTHESIZE(int, rx_flag, RxFlag);
	MYSQL_SYNTHESIZE(string, dosage_instruction, DosageInstruction);
	MYSQL_SYNTHESIZE(string, drug69_code, Drug69Code);
	MYSQL_SYNTHESIZE(string, total_volume, TotalVolume);
	MYSQL_SYNTHESIZE(string, dose_form_code, DoseFormCode);
	MYSQL_SYNTHESIZE(string, dose_unit_code, DoseUnitCode);
	MYSQL_SYNTHESIZE(string, package_unit_code, PackageUnitCode);
	MYSQL_SYNTHESIZE(string, stock_unit_code, StockUnitCode);
	MYSQL_SYNTHESIZE(string, method_code, MethodCode);
	MYSQL_SYNTHESIZE(string, rate_code, RateCode);
	MYSQL_SYNTHESIZE(double, dose, Dose);
	MYSQL_SYNTHESIZE(double, max_unit, MaxUnit);
	MYSQL_SYNTHESIZE(double, usage_limit, UsageLimit);
	MYSQL_SYNTHESIZE(string, location_id, LocationId);
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	MYSQL_SYNTHESIZE(string, org_id, OrgId);
	MYSQL_SYNTHESIZE(string, ingredient_item, IngredientItem);
	MYSQL_SYNTHESIZE(string, medicationdefinition, Medicationdefinition);
	MYSQL_SYNTHESIZE(string, ddd_code, DddCode);
	MYSQL_SYNTHESIZE(string, ddd_unit_code, DddUnitCode);
	MYSQL_SYNTHESIZE(string, min_rate_code, MinRateCode);
	MYSQL_SYNTHESIZE(string, max_rate_code, MaxRateCode);
	MYSQL_SYNTHESIZE(double, dose_unit_ratio, DoseUnitRatio);
	MYSQL_SYNTHESIZE(double, purchase_unit_ratio, PurchaseUnitRatio);
	MYSQL_SYNTHESIZE(double, stock_unit_ratio, StockUnitRatio);
	MYSQL_SYNTHESIZE(double, package_unit_ratio, PackageUnitRatio);

public:
	MedicationDefinitionDO()
		: BaseDO("med_medication_definition")
	{
		// Common audit fields
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "dt", created_at, false);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updated_at, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", created_by, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updated_by, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "b", is_deleted, false);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deleted_at, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deleted_by, true);
		MYSQL_ADD_FIELD_NULLABLE("version", "i", version, false);

		// Business fields
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", bus_no, false);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("domain_enum", "s", domain_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("med_version", "s", med_version, true);
		MYSQL_ADD_FIELD_NULLABLE("name_en", "s", name_en, true);
		MYSQL_ADD_FIELD_NULLABLE("py_str", "s", py_str, true);
		MYSQL_ADD_FIELD_NULLABLE("wb_str", "s", wb_str, true);
		MYSQL_ADD_FIELD_NULLABLE("category_code", "s", category_code, true);
		MYSQL_ADD_FIELD_NULLABLE("merchandise_name", "s", merchandise_name, true);
		MYSQL_ADD_FIELD_NULLABLE("merchandise_py_str", "s", merchandise_py_str, true);
		MYSQL_ADD_FIELD_NULLABLE("merchandise_wb_str", "s", merchandise_wb_str, true);
		MYSQL_ADD_FIELD_NULLABLE("purchase_unit_code", "s", purchase_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("split_unit_code", "s", split_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("comprised_text", "s", comprised_text, true);
		MYSQL_ADD_FIELD_NULLABLE("ingredient", "s", ingredient, true);
		MYSQL_ADD_FIELD_NULLABLE("dose_from", "i", dose_from, true);
		MYSQL_ADD_FIELD_NULLABLE("approval_number", "s", approval_number, true);
		MYSQL_ADD_FIELD_NULLABLE("yb_match_flag", "i", yb_match_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("yb_no", "s", yb_no, true);
		MYSQL_ADD_FIELD_NULLABLE("pharmacology_category_code", "s", pharmacology_category_code, true);
		MYSQL_ADD_FIELD_NULLABLE("skin_test_flag", "i", skin_test_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("inject_flag", "i", inject_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("manufacturer_id", "s", manufacturer_id, true);
		MYSQL_ADD_FIELD_NULLABLE("manufacturer_text", "s", manufacturer_text, true);
		MYSQL_ADD_FIELD_NULLABLE("supply_id", "s", supply_id, true);
		MYSQL_ADD_FIELD_NULLABLE("restricted_flag", "i", restricted_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("restricted_scope", "s", restricted_scope, true);
		MYSQL_ADD_FIELD_NULLABLE("active_flag", "i", active_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("children_flag", "i", children_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("characteristic", "i", characteristic, true);
		MYSQL_ADD_FIELD_NULLABLE("item_min_quantity", "d", item_min_quantity, true);
		MYSQL_ADD_FIELD_NULLABLE("item_max_quantity", "d", item_max_quantity, true);
		MYSQL_ADD_FIELD_NULLABLE("def_encounter_unit_code", "s", def_encounter_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("def_inhospital_unit_code", "s", def_inhospital_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("national_drug_code", "s", national_drug_code, true);
		MYSQL_ADD_FIELD_NULLABLE("part_attribute_enum", "s", part_attribute_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("antibiotic_code", "s", antibiotic_code, true);
		MYSQL_ADD_FIELD_NULLABLE("restricted_enum", "s", restricted_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("self_flag", "i", self_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("antibiotic_flag", "i", antibiotic_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("basic_flag", "i", basic_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("tho_part_attribute_enum", "s", tho_part_attribute_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("chrgitm_lv", "i", chrgitm_lv, true);
		MYSQL_ADD_FIELD_NULLABLE("rx_flag", "i", rx_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("dosage_instruction", "s", dosage_instruction, true);
		MYSQL_ADD_FIELD_NULLABLE("drug69_code", "s", drug69_code, true);
		MYSQL_ADD_FIELD_NULLABLE("total_volume", "s", total_volume, true);
		MYSQL_ADD_FIELD_NULLABLE("dose_form_code", "s", dose_form_code, true);
		MYSQL_ADD_FIELD_NULLABLE("dose_unit_code", "s", dose_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("package_unit_code", "s", package_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("stock_unit_code", "s", stock_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("method_code", "s", method_code, true);
		MYSQL_ADD_FIELD_NULLABLE("rate_code", "s", rate_code, true);
		MYSQL_ADD_FIELD_NULLABLE("dose", "d", dose, true);
		MYSQL_ADD_FIELD_NULLABLE("max_unit", "d", max_unit, true);
		MYSQL_ADD_FIELD_NULLABLE("usage_limit", "d", usage_limit, true);
		MYSQL_ADD_FIELD_NULLABLE("location_id", "s", location_id, true);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("org_id", "s", org_id, true);
		MYSQL_ADD_FIELD_NULLABLE("ingredient_item", "s", ingredient_item, true);
		MYSQL_ADD_FIELD_NULLABLE("medicationdefinition", "s", medicationdefinition, true);
		MYSQL_ADD_FIELD_NULLABLE("ddd_code", "s", ddd_code, true);
		MYSQL_ADD_FIELD_NULLABLE("ddd_unit_code", "s", ddd_unit_code, true);
		MYSQL_ADD_FIELD_NULLABLE("min_rate_code", "s", min_rate_code, true);
		MYSQL_ADD_FIELD_NULLABLE("max_rate_code", "s", max_rate_code, true);
		MYSQL_ADD_FIELD_NULLABLE("dose_unit_ratio", "d", dose_unit_ratio, true);
		MYSQL_ADD_FIELD_NULLABLE("purchase_unit_ratio", "d", purchase_unit_ratio, true);
		MYSQL_ADD_FIELD_NULLABLE("stock_unit_ratio", "d", stock_unit_ratio, true);
		MYSQL_ADD_FIELD_NULLABLE("package_unit_ratio", "d", package_unit_ratio, true);
	}

	MedicationDefinitionDO(MedicationDefinitionDO&&) = default;
	MedicationDefinitionDO& operator=(MedicationDefinitionDO&&) = default;
};

typedef std::shared_ptr<MedicationDefinitionDO> PtrMedicationDefinitionDO;

#endif // !_MEDICATION_DEFINITION_DO_
